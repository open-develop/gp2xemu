#ifndef _x86FPU_h_
#define _x86FPU_h_
#define ST0 0
#define ST1 1
#define ST2 2
#define ST3 3
#define ST4 4
#define ST5 5
#define ST6 6
#define ST7 7

typedef enum{
	ST=0
}x86FPUReg;

void f2xm1(void);
void fabs(void);
void faddST0(x86FPUReg );
void faddSTi(x86FPUReg );
void faddpSTi(x86FPUReg );
void faddp(void);

#endif
