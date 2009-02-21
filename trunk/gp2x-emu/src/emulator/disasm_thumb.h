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

#ifndef DISASM_THUMB_H_INCLUDED
#define DISASM_THUMB_H_INCLUDED
#include <stdlib.h>
#include <stdint.h>

typedef struct THUMB_bits
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
} THUMB_Bits;

typedef struct THUMB_Nibbles
{
    uint32_t nibble0 : 4;
    uint32_t nibble1 : 4;
    uint32_t nibble2 : 4;
    uint32_t nibble3 : 4;
} THUMB_Nibbles;

typedef struct THUMB_Bytes
{
    unsigned char byte0, byte1;
} THUMB_Bytes;

typedef union THUMB_Word
{
    THUMB_Bits bits;
    THUMB_Nibbles nibbles;
    THUMB_Bytes bytes;
    unsigned short word;
} THUMB_Word;

int ARMV4_ParseThumb(THUMB_Word);

#endif /* DISASM_THUMB_H_INCLUDED */

