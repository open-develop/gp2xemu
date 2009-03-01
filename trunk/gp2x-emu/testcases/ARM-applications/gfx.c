
void entrypoint(void);
unsigned long rotate_right(unsigned long val, unsigned long amount);

void entrypoint(void)
{
    int i;
    const unsigned long VIDEOMEM_LEN = 320*240;
    volatile unsigned long* VIDEOMEM_START = (volatile unsigned long*)0x80000000;
    volatile unsigned long* VIDEOMEM_UPDATE = (volatile unsigned long*)0x1C2004;
    
    unsigned long val = 0x00FF00FF;
    while(1){
        for(i=0;i<VIDEOMEM_LEN;++i)
            VIDEOMEM_START[i] = rotate_right(val, (i & 31));
        *VIDEOMEM_UPDATE = 1;
    }
    return;
}

unsigned long rotate_right(unsigned long val, unsigned long amount)
{
    return (val >> amount) | (val << (32UL - amount));
}
