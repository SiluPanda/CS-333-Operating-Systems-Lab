#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(){
	pid_t pid = fork();

	if(pid == 0){
		char *args[] = {"./mycat", 0};
		execvp(args[0], args);
	}
	else{
		int status;
		wait(&status);
		printf("Parent: The parent has terminated \n");
	}
}