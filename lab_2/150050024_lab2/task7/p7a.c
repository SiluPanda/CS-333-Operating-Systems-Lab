#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

void rec_fork (int n)
{
   
   pid_t process=fork();

   
   if(n==0)
   {
     return;
   }	
   
   else{
	   	if(process!=0)
	   {
	   	printf("child  %u is created\n",getpid() );
	   	wait(NULL);
	   	printf("child  %u exited\n",getpid() );

	   }
	   else
	   {
	   	rec_fork(n-1);
	   }
   }
}


int main(int argc, char *argv[]){
	//printf("%s\n", argv[1]);
	int n = atoi(argv[1]);

	

	pid_t p = fork();
	if(p != 0){
		printf("Parent is: %d\n", getpid());
		printf("Number of children: %d\n", n);
		wait(NULL);
		printf("Parent exited\n");
	}
	else{
		rec_fork(n);
	}


	
	//recursive(n);
	
	
	//recursive(n);



}