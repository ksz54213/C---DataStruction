#include<stdio.h>
#include<stdlib.h>
#include<time.h>
int a[10];
int out,in = 0;
/*struct circle{
	int in;
	int out;
	struct circle *next;
}typedef struct circle Circle;*/


int main(void){
	int n,b;
	for(b=0;b<10;b++){
		scanf("%d",&n);
		a[b]= n ;
	}
	int end=0,count=1;
	while(1){
		
		printf("%d, ",a[end++]);
		if(end==10){
			printf("the circle has run %d times\n",count++);
			end=0;
		}
		Sleep(500);
	}
	
	
	
	
}
