#ifndef _MMU_h_
#define _MMU_h_
#include <arm_emu.h>
#include <arm920t.h>






/* these are the positions of the bits in the CP15 register 1 */
#define MMU_ACTIVE		(CP15_1.uVal&0x1) 
#define ALIGNMENT_CHECK 	(CP15_1.uVal&(0x1<<1))
#define SYSTEM_PROTECTION 	(CP15_1.uVal&(0x1<<8))
#define ROM_PROTECTION		(CP15_1.uVal&(0x1<<9))

/* domain access values */
#define NO_ACCESS		(0x0)
#define CLIENT			(0x1)
#define MANAGER			(0x3)



/* fault/exception  types  which can be set in fsr */
#define TERMINAL_EXCEPTION		(0x2)
#define VECTOR_EXCEPTION		(0x0)
#define ALIGNMENT_FAULT1		(0x1)
#define ALIGNMENT_FAULT2		(0x3)
#define FIRST_LEVEL_EAT			(0xc)
#define SECOND_LEVEL_EAT		(0xe)
#define TRANSLATION_FAULT		(0x2)
#define TRANSLATION_FAULT_SECTION 	(0x5)
#define TRANSLATION_FAULT_PAGE		(0x7)
#define DOMAIN_FAULT_SECTION		(0x9)
#define DOMAIN_FAULT_PAGE		(0xb)
#define PERMISSION_FAULT_SECTION 	(0xd)
#define PERMISSION_FAULT_PAGE		(0xf)
#define LINEFETCH_ABORT_SECTION		(0x4)
#define LINEFETCH_ABORT_PAGE		(0x6)
#define EA_NOLINEFETCH_SECTION		(0x8)
#define EA_NOLINEFETCH_PAGE		(0xa)



/* MMU access permissions */
#define AP

int initMemory(void);

u32 translateAddress(u32 );
u32 readMemU32(u32 );
u16 readMemU16(u32 );
u8  readMemU8(u32 );

void writeMemU32(u32 , u32);

typedef struct {
	size_t size;
	void *space;
}MEMBLOCK;


struct  tlbEntry {
	u32 vAddr;
	u32 pAddr;
};



struct flDesc{

	u32 type:2;		/* type of descriptor */
	u32 cb:2;		/* cachable and bufferable-bits */
	u32 resv1:1;		/* the meaning of that bit is implementation defined */
	u32 domain:4;		/* domain field specfies one of 16 possible domains */
	u32 resv2:1;		/* not used should be zero */
	u32 perm:2;		/* access permissions */
	u32 resv3:8;		/* not used should be zero */
	u32 sBase:12;		/* section-base form top 12-bits of physical address */
};


/* first level descriptors */
struct coarseDesc{
	u32 type:2;
	u32 imp:3;
	u32 domain:4;
	u32 sbz:1;
	u32 baseAddr:22;
};



struct sectionDesc{

	u32 type:2;
	u32 c:1;
	u32 b:1;
	u32 imp:1;
	u32 domain:4;
	u32 sbz1:1;
	u32 ap:2;
	u32 sbz2:8;
	u32 baseAddr:12;
};


struct fineDesc{
	u32 type:2;
	u32 imp:3;
	u32 domain:4;
	u32 sbz:3;
	u32 baseAddr:20;
};


/* second level descriptor  */

struct largePage{

	u32 type:2;
	u32 b:1;
	u32 c:1;
	u32 ap0:2;
	u32 ap1:2;
	u32 ap2:2;
	u32 ap3:2;
	u32 sbz:4;
	u32 baseAddr:15;
};



struct smallPage{

	u32 type:2;
	u32 b:1;
	u32 c:1;
	u32 ap0:2;
	u32 ap1:2;
	u32 ap2:2;
	u32 ap3:2;
	u32 baseAddr:20;
};

struct finePage{

	u32 type:2;
	u32 b:1;
	u32 c:1;
	u32 ap:2;
	u32 sbz:4;
	u32 baseAddr:22;
};


#endif 
