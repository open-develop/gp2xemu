#ifndef ADRMODE1_GUARD
#define ADRMODE1_GUARD

#define PSR_STATUS_FLAGS 0x1B
#define PSR_V_FLAG(x) ((x>>28) & 0x1)
#define PSR_C_FLAG(x) ((x>>29) & 0x1)
#define PSR_Z_FLAG(x) ((x>>30) & 0x1)
#define PSR_N_FLAG(x) ((x>>31) & 0x1)

typedef struct
{
    u32 shifter_operand;
    u32 shifter_carry_out;
} shifter_result;

#endif
