#include "types.h"
#include "stat.h"
#include "user.h"

int main(int argc, char *argv[]){
	int pid = fork();
	char *new_arg[argc];
	
	for(int i = 1; i < argc; i++){
		new_arg[i-1] = argv[i];
	}
	new_arg[argc-1] = '\0';

	
	if(pid == 0){
		exec(new_arg[0], new_arg);
	}
	else{
		wait();


	}
	exit();
}
