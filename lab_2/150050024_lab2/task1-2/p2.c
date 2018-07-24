#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(){
	pid_t  pid  = fork();
	 
	if (pid == 0) {
	    printf("Child: My Process ID is: %d\n", getpid());
	    printf("Child: The Parent process ID is: %d\n", getppid());
	}

	else{
		wait(NULL);
		printf("Parent: My Process ID is: %d\n", getpid());
		printf("Parent: The parent process ID is: %d\n", pid);
		printf("Parent: The child with process ID %d has terminated \n", pid);

	}

}