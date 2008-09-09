#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <sys/mman.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <assert.h>
#include <arm_emu.h>
#include <arm920t.h>
#include <MMU.h>



#ifndef MAP_ANONYMOUS
#define MAP_ANONYMOUS 0x20
#endif 

#define TLB_CACHE_SIZE 	64

#define MEMSIZE (0x20*0x400*0x400)


static struct tlbEntry tlbCache[TLB_CACHE_SIZE];


#define REC_MEM	(1*0x400*0x400)




MEMBLOCK physMem;
MEMBLOCK recMem;
MEMBLOCK fileImage;







void initMem(const char *image, size_t size){
	
	int fd;
	u32 counter;
	struct stat k;

	if(image){
		
		fd = open(image,O_RDONLY);
		if(fd < 0){
			fprintf(stderr,"opening() of %s failed\n",image);
			exit(EXIT_FAILURE);
		}

		stat(image,&k);
		fileImage.space = mmap(NULL,k.st_size,PROT_READ,MAP_SHARED,fd,0);
		fileImage.size = k.st_size;

		if(fileImage.space == MAP_FAILED){
			fprintf(stderr,"mmap()'ing of %s failed\n",image);
			exit(EXIT_FAILURE);
		}

		physMem.space = mmap(NULL,size,PROT_READ|PROT_WRITE,MAP_SHARED|MAP_ANONYMOUS,-1,0);
		physMem.size = size;

		if(MAP_FAILED == physMem.space){
			fprintf(stderr,"mmap()'ing of physical Mem failed\n");
			exit(EXIT_FAILURE);
		}

		recMem.space = mmap(NULL,REC_MEM,PROT_READ|PROT_WRITE|PROT_EXEC,MAP_SHARED|MAP_ANONYMOUS,-1,0);
		recMem.size = REC_MEM;

		if(MAP_FAILED == recMem.space ){
			fprintf(stderr,"mmap()'ing of rec Mem failed\n");
			exit(EXIT_FAILURE);
		}

		for(counter=0;counter<fileImage.size;counter++){
			((u8*)physMem.space)[counter]=((u8*)fileImage.space)[counter];
		}
	}
}




static int tlbLookup(u32 addr){

	int index=0;

	while(index<TLB_CACHE_SIZE){
		if(addr==tlbCache[index].vAddr){
			return index;
		}
		index++;
	}

	return -1;
}

static void faultHandler(u32 faultID, u32 addr){


	switch(faultID){

		case TERMINAL_EXCEPTION:
		case VECTOR_EXCEPTION:
		case ALIGNMENT_FAULT1:
		case ALIGNMENT_FAULT2:FSR.uVal=faultID;FAR.uVal=addr;break;
		case FIRST_LEVEL_EAT:
		case SECOND_LEVEL_EAT:
		case TRANSLATION_FAULT_SECTION:
		case TRANSLATION_FAULT_PAGE:
		case DOMAIN_FAULT_SECTION:
		case DOMAIN_FAULT_PAGE:
		case PERMISSION_FAULT_SECTION:
		case PERMISSION_FAULT_PAGE:
		case LINEFETCH_ABORT_SECTION:
		case LINEFETCH_ABORT_PAGE:
		case EA_NOLINEFETCH_SECTION:
		case EA_NOLINEFETCH_PAGE:break;
		default:fprintf(stderr,"unknown faultID\n");break;
			
	}

}


static void handleFault(u32 addr){

	CP15_6.uVal=addr;
	exit(EXIT_FAILURE);
}

static u32 handleSecondLevelDesc(u32 desc, u32 addr){

	u32 pAddr;

	/* i dont distinguish between fine and coarse descriptors */


	switch(desc&0x3){
		case 0:handleFault(addr);break;		
		case 1:{ 			/* we have a large page */
			       pAddr=(desc&(0x7fffffU<<15))|(addr&0x7fffff);
				       
		       }break;
		case 2:{
			       /* small page */
			      pAddr=(desc&(0xfffffU<<12))|(addr&0xfffff);
		       }break;
		case 3:{
			       /* tiny page,  actually tiny-pages shouldnt appear in coarse-tables
				* if they do so the results are upredictable according to the
				* manual */
			       pAddr=(desc&(0x3fffffU<<10))|(addr&0x3ff);
		       }break;
	}

	return pAddr;
}

/* translates virtual to 'physical' address */

u32 translateAddress(u32 addr){

	u32 tBase;
	u32 pAddr;
	u32 sLDesc;
	u32 fLDesc; 
	int index;

	if(ALIGNMENT_CHECK && addr&0x3){
		faultHandler(ALIGNMENT_FAULT1,addr);
	}
	else{

		if(-1==(index=tlbLookup(addr))){
			
#if 0
			tBase=CP15_2.uVal&(0x3ffffU<<14);
			tBase|=(addr>>18);
			fLDesc=*((u32 *)tBase);
#endif 

			fLDesc=*((u32 *)(((CP15_2.uVal&(0x3ffffU<<14))|(addr>>18)))); 

			switch(fLDesc&0x3U){
			case 0:handleFault(addr);break; 	/* not mapped addr */
			case 1:{
				       sLDesc=*((u32 *)((fLDesc&(0x3fffffU<<10))|(addr&(0xff<<12))));
				       /*sLDesc=*((u32 *)sLDesc);*/
				       pAddr=handleSecondLevelDesc(sLDesc,addr);

			       }break;
			case 2:{
				       pAddr=(fLDesc&(0xfffU<<20))|(addr&0xfffff);
			       }break;

			case 3:{
					sLDesc=*((u32 *)((fLDesc&(0x3fffffU<<10))|(addr&(0x3ff<<10))));
					/*sLDesc=*((u32 *)sLDesc);*/
					pAddr=handleSecondLevelDesc(sLDesc,addr);
			       }break;
			}
			/*pAddr=(fLDesc&(0xfff<<20))|(addr&0xfffff);*/

		}
		else return tlbCache[index].pAddr;
	}

	return pAddr;
}


void *readMemBlock(void *addr, size_t size){
	size++;
	return addr;
}


u32 readMemU32(u32 addr){

	u32 *pAddr = (u32 *)translateAddress(addr);
	return *pAddr;
}


u16 readMemU16(u32 addr){
	/* actually necessary? */
	return addr;

}


u8 readMemU8(u32 addr){

	u8 *pAddr = (u8 *)translateAddress(addr);
	return *pAddr;
}


void writeMemU32(u32 addr, u32 val){

	u32 *pAddr = (u32 *)translateAddress(addr);
	*pAddr = val;
}


void writeMemU16(u32 addr, u16 val){

	u16 *pAddr = (u16 *)translateAddress(addr);
	*pAddr = val;

}


void writeMemU8(u32 addr, u8 val){

	u8 *pAddr = (u8 *)translateAddress(addr);
	*pAddr = val;
}
