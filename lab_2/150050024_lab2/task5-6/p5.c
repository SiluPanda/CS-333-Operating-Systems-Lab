#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(){
	pid_t  pid  = fork();
	 
	if (pid != 0) {
	    printf("Parent: My Process ID is: %d\n", getpid());
		printf("Parent: The child process ID is: %d\n", pid);
		sleep(5);
		printf("Parent: The parent has terminated\n");
	}

	else{
		
		printf("Child: My Process ID is: %d\n", getpid());
		printf("Child: The parent process ID is: %d\n", getppid());

		sleep(10);

		printf("Child: My Process ID is: %d\n", getpid());
		printf("Child: The parent process ID is: %d\n", getppid());



		

	}

}