#ifndef DISASM_ARM_H_INCLUDED
#define DISASM_ARM_H_INCLUDED
#include <stdlib.h>
#include <stdint.h>

typedef struct ARM_bits
{
    uint32_t bit0 : 1;
    uint32_t bit1 : 1;
    uint32_t bit2 : 1;
    uint32_t bit3 : 1;
    uint32_t bit4 : 1;
    uint32_t bit5 : 1;
    uint32_t bit6 : 1;
    uint32_t bit7 : 1;
    uint32_t bit8 : 1;
    uint32_t bit9 : 1;
    uint32_t bit10 : 1;
    uint32_t bit11 : 1;
    uint32_t bit12 : 1;
    uint32_t bit13 : 1;
    uint32_t bit14 : 1;
    uint32_t bit15 : 1;
    uint32_t bit16 : 1;
    uint32_t bit17 : 1;
    uint32_t bit18 : 1;
    uint32_t bit19 : 1;
    uint32_t bit20 : 1;
    uint32_t bit21 : 1;
    uint32_t bit22 : 1;
    uint32_t bit23 : 1;
    uint32_t bit24 : 1;
    uint32_t bit25 : 1;
    uint32_t bit26 : 1;
    uint32_t bit27 : 1;
    uint32_t bit28 : 1;
    uint32_t bit29 : 1;
    uint32_t bit30 : 1;
    uint32_t bit31 : 1;
} ARM_Bits;

typedef struct ARM_Nibbles
{
    uint32_t nibble0 : 4;
    uint32_t nibble1 : 4;
    uint32_t nibble2 : 4;
    uint32_t nibble3 : 4;
    uint32_t nibble4 : 4;
    uint32_t nibble5 : 4;
    uint32_t nibble6 : 4;
    uint32_t nibble7 : 4;
} ARM_Nibbles;

typedef struct ARM_Bytes
{
    unsigned char byte0, byte1, byte2, byte3;
} ARM_Bytes;

typedef union ARM_Word
{
    ARM_Bits bits;
    ARM_Nibbles nibbles;
    ARM_Bytes bytes;
    uint32_t word;
} ARM_Word;

typedef enum ARMV4_ConditionType
{
    ARM_CondEQ = 0,
    ARM_CondNE,
    ARM_CondCS,
    ARM_CondCC,
    ARM_CondMI,
    ARM_CondPL,
    ARM_CondVS,
    ARM_CondVC,
    ARM_CondHI,
    ARM_CondLS,
    ARM_CondGE,
    ARM_CondLT,
    ARM_CondGT,
    ARM_CondLE,
    ARM_CondAL,
    ARM_CondNV
}ARMV4_ConditionType;

typedef enum ARMV4_InstructionType
{
    ARMV4_TypeUndefined = 0,
    ARMV4_TypeUnpredictable,
    ARMV4_TypeDataProcessing,
    ARMV4_TypeMultiplication,
    ARMV4_TypeAtomicSwap,
    ARMV4_TypeLoadStoreExtra, /* new halfword, sign halfword and signed byte load/stores */
    ARMV4_TypeStatusRegister,
    ARMV4_TypeLoadStoreSingle,
    ARMV4_TypeLoadStoreMultiple,
    ARMV4_TypeBranch, /* B, BL and BX */
    ARMV4_TypeLoadStoreCoprocessor,
    ARMV4_TypeDataProcessingCoprocessor,
    ARMV4_TypeRegisterTransferCoprocessor,
    ARMV4_TypeSoftwareInterrupt
} ARMV4_InstructionType;

/* This handy function parses ARMv4 instructions.
 * Later versions of the instruction set should be easy to add as standalone
 * parser functions, as well as splitting the parsing up in worker threads.
 */
int ARMV4_ParseInstruction(ARM_Word instr);

#endif // DISASM_ARM_H_INCLUDED
