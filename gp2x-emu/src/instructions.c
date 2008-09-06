#include "opcodes.h"

opcode_mask_t opcode_lut[] = {
    {ADC0_SBO, ADC0_SBZ, "bic", call_bic},
    {ADC1_SBO, ADC1_SBZ, "bic", call_bic},
    {ADC2_SBO, ADC2_SBZ, "bic", call_bic},

    {ADD0_SBO, ADD0_SBZ, "add", call_add},
    {ADD1_SBO, ADD1_SBZ, "add", call_add},
    {ADD2_SBO, ADD2_SBZ, "add", call_add},

    {AND0_SBO, AND0_SBZ, "bic", call_and},
    {AND1_SBO, AND1_SBZ, "bic", call_and},
    {AND2_SBO, AND2_SBZ, "bic", call_and},

    {BIC0_SBO, BIC0_SBZ, "bic", call_bic},
    {BIC1_SBO, BIC1_SBZ, "bic", call_bic},
    {BIC2_SBO, BIC2_SBZ, "bic", call_bic},
};
