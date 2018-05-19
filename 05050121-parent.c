#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
int main(int argc, char *argv[])
{
	const char *name = "COLLATZ";
	const int SIZE = 4096;

	pid_t pid;
	int shm_fd;
	void *ptr;

	if (argc == 1) {
		fprintf(stderr,"Usage: ./a.out <starting value>\n");
		return -1;
	}

	pid = fork();
	if (pid < 0) {
		fprintf(stderr, "Unable to fork child\n");
		return -1;
	}
	else if (pid == 0) { 

		execlp("./child","./child",argv[1],NULL);
	}
	else { 
		fprintf(stderr,"Child Process ID returned by fork= %d\n", pid);
		wait(NULL);
		shm_fd = shm_open(name, O_RDONLY, 0666);
		
		if (shm_fd == -1) {
			printf("shared memory failed\n");
			exit(-1);
		}
		
		ptr = mmap(0,SIZE, PROT_READ, MAP_SHARED, shm_fd, 0);  

		if (ptr == MAP_FAILED) {
			printf("Map failed\n");
			exit(-1);
		}

		while(1){
			
			if(*(char*)ptr==0)
				break;
			else{
					printf("%s ",(char *)ptr );
				ptr+=4;
			}
		}
		printf("\n");
	
		if (shm_unlink(name) == -1) {
			printf("Error removing %s\n",name);
			exit(-1);
		}


	}

	return 0;
}