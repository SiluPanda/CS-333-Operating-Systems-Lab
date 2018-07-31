#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <time.h>

void sig_handler(int sig){
	pid_t pid;
	pid = wait(NULL);
	printf("Parent %d: Child %d is exited \n" ,getpid(), pid);
}

int main(){
	signal(SIGCHLD, sig_handler);

	pid_t pid = fork();
	if(pid == 0){
		int t1 = 9; //sleep time for child process
		int t2 = 4; //sleep time for grand child process
		printf("Child %d is created by parent %d (sleeps for %d seconds) \n", getpid(), getppid(), t1);
		pid_t pi = fork();
		
		if(pi == 0){
			printf("Child %d is created by parent %d (sleeps for %d seconds)\n", getpid(), getppid(),t2);
			sleep(t2);
			exit(0);
		}
		else{
		sleep(t1);
		
		exit(0);
	}
	}
;
	while(1){}
}