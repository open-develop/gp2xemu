#ifndef _ARMMisc_h_
#define _ARMMisc_h_

void recNULL(void);
void recSWI(void);
void recSWP(void);
void recSWPB(void);
void recTEQi(void);
void recTEQs(void);
void recTSTi(void);
void recTSTs(void);
void recCMPi(void);
void recCMPs(void);
void recCMNi(void);
void recCMNs(void);

extern const u32 shift_table[];
extern  void (*shiftDispatch[])(x86GPReg);


#endif
