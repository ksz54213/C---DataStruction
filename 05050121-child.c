#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <string.h>
#include <unistd.h>
int main(int argc, char *argv[])
{
	const char *name = "COLLATZ";
	const int SIZE = 4096;

	pid_t pid;
	int shm_fd;
	void *ptr;
	int n;
	char str[128];

	if (argc == 1) {
		fprintf(stderr,"Usage: ./a.out <starting value>\n");
		return -1;
	}

	n = atoi(argv[1]); /* 從命令列取得要計算的考拉茲臆測數列第一個數字 */
	
	shm_fd = shm_open(name, O_CREAT | O_RDWR, 0666);

	
	ftruncate(shm_fd,SIZE);

	
	ptr = mmap(0,SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
	
	if (ptr == MAP_FAILED) {
		printf("Map failed\n");
		return -1;
	}
	const char* message0 = "Hell";
	const char* message1 = "str";
	const char* message2 = "steji";
	
	const int* message3 ;
	
	int num[128],end=0;
	num[end++]=n;
	while(1){
		
		if(n==1)
			break;
		else if(n%2==0){
			n/=2;
			num[end++]=n;
		}
		else{
			n*=3;
			n+=1;
			num[end++]=n;
		}
	}
	
	message3 = num;

	
	for (int i =0; i < end; i++)
	{
		sprintf(ptr,"%d",*(message3+i));
		ptr += sizeof(*(message3));
	}
	
	

	return 0;
	
}
