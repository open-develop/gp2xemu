#ifndef EMULATOR_H_INCLUDED
#define EMULATOR_H_INCLUDED
#include "cpu/cpu.h"
#include "peripherals/memory.h"
#include "disasm_arm.h"
#include "disasm_thumb.h"
#include "instrset_armv4.h"
#include "instrset_thumb.h"

typedef struct ARM_Emulator
{
    ARM_CPU cpu;
    ARM_Memory memory;
} ARM_Emulator;

#endif
