#ifndef _arm_emu_h_
#define _arm_emu_h_
#include <stdint.h>
#include <assert.h>
#ifndef TRUE
#define TRUE 	1
#endif
#ifndef FALSE
#define FALSE 	0
#endif

#define __register 	register
/*#define __inline	inline*/

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef int8_t  s8;
typedef int16_t s16;
typedef int32_t s32;

#if 0
typedef unsigned char u8
typedef unsigned short u16;
typedef unsigned int u32;
/*typedef unsigned long long u64;*/
typedef signed char s8;
typedef signed short s16;
typedef signed int s32;
/*typedef signed long long s64;*/
#endif 

#endif
