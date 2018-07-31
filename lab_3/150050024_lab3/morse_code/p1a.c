#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

void sig_handler_sigint(int sig){

	printf("\nInterrupt SIGINT received. \nDo you really want to quit (y|n)");
	char in;
	in = getchar();
	if(in == 'y'){
		exit(0);
	}
	getchar();

}
	
void sig_handler_sigterm(int sig){

	printf("\nInterrupt SIGTERM received. \nDo you really want to quit (y|n)");
	char in;
	in = getchar();
	if(in == 'y'){
		exit(0);
	}
	getchar();

	
}

int main(){
	signal(SIGINT, sig_handler_sigint);
	signal(SIGTERM, sig_handler_sigterm);

	while(1){

	}


}
