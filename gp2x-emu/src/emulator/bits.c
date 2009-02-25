#include "bits.h"
#include "assert.h"

void swap32(uint32_t* restrict ptr1, uint32_t* restrict ptr2)
{
    uint32_t tmp;
    tmp = *ptr1;
    *ptr1 = *ptr2;
    *ptr2 = tmp;
}

void swap16(uint16_t* restrict ptr1, uint16_t* restrict ptr2)
{
    uint16_t tmp;
    tmp = *ptr1;
    *ptr1 = *ptr2;
    *ptr2 = tmp;
}

void swap8 (uint8_t*  restrict ptr1, uint8_t*  restrict ptr2)
{
    uint8_t tmp;
    tmp = *ptr1;
    *ptr1 = *ptr2;
    *ptr2 = tmp;
}

int clz32(uint32_t value)
{
    uint32_t i;
    int count;
    if(value & (1UL<<31UL))
        return 0;
    for(i=31UL, count=0; i >= 0; ++count, --i){
        if((value & (1UL<<i)))
            break;
    }
    return count;
}

int clz16(uint16_t value)
{
    uint16_t i;
    int count;
    if(value & (1U<<15U))
        return 0;
    for(i=15U, count=0; i >= 0; ++count, --i){
        if((value & (1U<<i)))
            break;
    }
    return count;
}

int clz8(uint8_t value)
{
    uint8_t i;
    int count;
    if(value & (1U<<7U))
        return 0;
    for(i=7U, count=0; i >= 0; ++count, --i){
        if((value & (1U<<i)))
            break;
    }
    return count;
}

uint32_t signextend8(uint8_t value)
{
    return value |= ((value & (1U<<7U)) ? 0xFFFFFF00 : 0x0);
}

uint32_t signextend16(uint16_t value)
{
    return value |= ((value & (1U<<15U)) ? 0xFFFF0000 : 0x0);
}

