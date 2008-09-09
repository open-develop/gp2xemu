#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <unistd.h>
#include <fcntl.h>
#include <arm_emu.h>
#include <arm920t.h>
#include <ARMArit.h>
#include <ARMrec.h>
#include <x86.h>

u8 *code_ptr;

int main(void){

	int fd=open("/home/dr_evil/c_projects/arm/arm",O_RDWR|O_CREAT,0777);
	struct stat t;
	u8 *oldcode;
	void *file;


	if(fd >= 0){

		fstat(fd,&t);
		file=mmap(NULL,t.st_size,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
		code_ptr=malloc(1024);
		if(file !=MAP_FAILED){
			printf("%p\n",file);
			file=((char *)file)+0x718;
			printf("%p\n",file);
			recompile(file,50);
		}
		else printf("mmap() failed\n");
	}
	else printf("open() failed\n");
	return 0;
}
