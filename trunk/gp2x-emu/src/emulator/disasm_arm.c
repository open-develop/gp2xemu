/*
Copyright (c) 2009,
Mads Andreas Elvheim

Permission is hereby granted, free of charge, to any person
obtaining a copy of this software and associated documentation
files, to deal in the software without
restriction, including without limitation the rights to use,
copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the software, and to permit persons to whom the
software is furnished to do so, subject to the following
conditions:

The above copyright notice and this permission notice shall be
included in all copies or substantial portions of the software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
OTHER DEALINGS IN THE SOFTWARE.
*/

#include <stdio.h>
#include "disasm_arm.h"

/* static const char* cond[] = {"eq","ne","cs","cc","mi","pl","vs","vc","hi","ls","ge","lt","gt","le","", "unpredictable"}; */

static int ARMV4_ParseInstrExt0(ARM_Word instr)
{
    /* this function depends on prior check of whether bit4 is zero */
    if(!instr.nibbles.nibble1){
        if(instr.bits.bit21){
            /* TODO: Add bits[15:12] = 1 [11:8] = 0 */
            /* msr */
            return ARMV4_TypeStatusRegister;
        }
        else{
            /* TODO: Add bits[19:16] = 1 [11:8] = 0 */
            /* mrs */
            return ARMV4_TypeStatusRegister;
        }
    }
    else{
        if(instr.bits.bit7){
            /* Undefined DSP instruction */
            return ARMV4_TypeUndefined;
        }
        else{
            return ARMV4_TypeUndefined;
        }
    }
    return ARMV4_TypeUndefined;
}

static int ARMV4_ParseInstrExt1(ARM_Word instr)
{
    /* opcode = bit[22:21] and bit[7:4] */
    unsigned long op = (instr.word >> 21) & 0x3;
    switch(instr.nibbles.nibble1)
    {
        case 0x1:
        /* BX or (undefined) CLZ */
            if(op == 0x1){
                /* BX */
                return ARMV4_TypeBranch; 
            }
            else{
                return ARMV4_TypeUndefined;
            }
        case 0x3:
        /* (undefined) BLX */
            return ARMV4_TypeUndefined;
        case 0x5:
        /* (undefined) DSP add/sub */
            return ARMV4_TypeUndefined;
        case 0x7:
        /* (undefined) BKPT */
            return ARMV4_TypeUndefined;
        default:
            return ARMV4_TypeUndefined;
    }
    /* make the compiler shut up */
    return ARMV4_TypeUndefined;
}

static int ARMV4_ParseInstrExt2(ARM_Word instr)
{
    /* MUL/MLA,SMLAL,SMULL,UMLAL,UMULL, STRH/LDRH, LDRSB, LDRH and two undefined*/
    unsigned long op = (instr.word >> 5) & 0x3;
    switch(op)
    {
        /* Multiply, multiply long, swap */
        case 0x0:
            if(!((instr.word >> 22) & 0x7)){
                if(instr.bits.bit21){
                    /* mla */
                    return ARMV4_TypeMultiplication;
                }
                else{
                    /* mul */
                    return ARMV4_TypeMultiplication;
                }
            }
            else if(((instr.word >> 23) & 0x3) == 0x1){
                switch((instr.word >> 21) & 0x3)
                {
                    case 0x0:
                        return ARMV4_TypeMultiplication; /* smull */
                    case 0x1:
                        return ARMV4_TypeMultiplication; /* smlal */
                    case 0x2:
                        return ARMV4_TypeMultiplication; /* umull */
                    case 0x3:
                        return ARMV4_TypeMultiplication; /* umlal */
                }
            }
            else if(((instr.word >> 20) & 0x1B) == 0x10)
            {
                if(instr.bits.bit22){
                    /* swapb */
                    return ARMV4_TypeAtomicSwap;
                }
                else{
                    /* swp */
                    return ARMV4_TypeAtomicSwap;
                }
            }
        /* Load/store half-word ldrh/strh*/
        case 0x1:
            return ARMV4_TypeLoadStoreExtra;
        /* Load signed half-word */
        case 0x2:
        case 0x3:
            /* TODO: check for L = 0 && S = 1 which is unpredictable */
            if(!instr.bits.bit22 && instr.bits.bit20){
                /* Register offset */
                if(instr.bits.bit5){
                    /* ldrsh */
                    return ARMV4_TypeLoadStoreExtra;
                }
                else{
                    /* ldrsb */
                    return ARMV4_TypeLoadStoreExtra;
                }
            }
            else if(instr.bits.bit22 && instr.bits.bit20){
                /* Immediate offset */
                if(instr.bits.bit5){
                    /* ldrsh */
                    return ARMV4_TypeLoadStoreExtra;
                }
                else{
                    /* ldrsb */
                    return ARMV4_TypeLoadStoreExtra;
                }
            }
            else{
                return ARMV4_TypeUndefined;
            }
        default:
            return ARMV4_TypeUndefined;
    }
    return ARMV4_TypeUndefined; /* Make the compiler shut up */
}

int ARMV4_ParseInstruction(ARM_Word instr)
{
    unsigned long op = (instr.word >> 25) & 0x7;
    switch(op)
    {
        case 0x0:
            if(!instr.bits.bit4){
                if(instr.bits.bit24 && !instr.bits.bit23 && !instr.bits.bit20){
                    return ARMV4_ParseInstrExt0(instr);
                }
                else{
                    /* dataproc immediate shift */
                    /*ParseInstrDataProc(instr);*/
                    return ARMV4_TypeDataProcessing;
                }
            }
            else if(!instr.bits.bit7){
                if(instr.bits.bit24 && !instr.bits.bit23 && !instr.bits.bit20){
                    /* misc */
                    return ARMV4_ParseInstrExt1(instr);
                }
                else{
                    /* dataproc register shift */
                    /* ParseInstrDataProc(instr); */
                    return ARMV4_TypeDataProcessing;
                }
            }
            else if(instr.bits.bit4 && instr.bits.bit7){
                /* Multipliers, extra load/stores */
                return ARMV4_ParseInstrExt2(instr);
            }
        case 0x1:
            if(instr.bits.bit24 && !instr.bits.bit23 && !instr.bits.bit20){
                if(instr.bits.bit21){
                    /* MSR immediate */
                    return ARMV4_TypeStatusRegister;
                }
                else{
                    /* undefined */
                    return ARMV4_TypeUndefined;
                }
            }
            else{
                /* dataproc immediate */
                return ARMV4_TypeDataProcessing;
            }
        case 0x2:
            /* load/store immediate offset */
            return ARMV4_TypeLoadStoreSingle;
        case 0x3:
            if(!instr.bits.bit4){
                /* load/store register offset */
                return ARMV4_TypeLoadStoreSingle;
            }
            else {
                /* undefined */
                return ARMV4_TypeUndefined;
            }
        case 0x4:
            /* load/store multiple */
            return ARMV4_TypeLoadStoreMultiple;
        case 0x5:
            /* B and BL */
            /* ParseInstrBranch(instr); */
            return ARMV4_TypeBranch;
        case 0x6:
            /* co-processor load/store (LDC/STC) and DSP register transfers (undefined)*/
            return ARMV4_TypeLoadStoreCoprocessor;
            break;
        case 0x7:
            if(instr.bits.bit24){
                /* SWI */
                return ARMV4_TypeSoftwareInterrupt;
            }
            else{
                if(instr.bits.bit4){
                    /* co-processor register transfers (MRC/MCR) */
                    return ARMV4_TypeRegisterTransferCoprocessor;
                }
                else{
                    /* co-processor data processing (CDP) */
                    return ARMV4_TypeDataProcessingCoprocessor;
                }
            }
        default:
            return ARMV4_TypeUndefined;
    }
    return ARMV4_TypeUndefined;
}
