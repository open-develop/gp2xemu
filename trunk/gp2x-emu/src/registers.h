#ifndef REGISTERS_H_
#define REGISTERS_H_

typedef unsigned int reg_t;
typedef union regs_t
{
    reg_t r[16];
    struct
    {
        reg_t r0;
        reg_t r1;
        reg_t r2;
        reg_t r3;
        reg_t r4;
        reg_t r5;
        reg_t r6;
        reg_t r7;
        reg_t r8;
        reg_t r9;
        reg_t r10;
        reg_t r11;
        reg_t r12;
        reg_t sp;
        reg_t lr;
        reg_t pc;
        reg_t cpsr;

        reg_t svc_lr;
        reg_t svc_sp;
        reg_t svc_spsr;

        reg_t abt_lr;
        reg_t abt_sp;
        reg_t abt_spsr;

        reg_t und_lr;
        reg_t und_sp;
        reg_t und_spsr;

        reg_t irq_lr;
        reg_t irq_sp;
        reg_t irq_spsr;

        reg_t fiq_r8;
        reg_t fiq_r9;
        reg_t fiq_r10;
        reg_t fiq_r11;
        reg_t fiq_r12;
        reg_t fiq_lr;
        reg_t fiq_sp;
        reg_t fiq_spsr;
    };
} regs_t;

#endif
