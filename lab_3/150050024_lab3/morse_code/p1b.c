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
	printf("Child %d is exited \n" , pid);
}



int main ( int argc, char *argv[] )
{	

	signal(SIGCHLD, sig_handler);
    int i;
    pid_t pid;

	for(i = 0; i < atoi(argv[1]); i++) {
		
    	int sleep_time = (rand()%(9)) + 2;
	    pid = fork();

	    if(pid < 0) {
	        exit(1);
	    } 

	    else if (pid == 0) {
	    	// srand(current_timestamp());
	        printf("Child %d is created (sleeps for %d seconds)\n", getpid(), sleep_time);
	        sleep(sleep_time);
	        exit(0); 
	    } 

	    
	}

	while(1){}
}
