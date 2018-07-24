#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>


int main() {

	pid_t child_pid =fork();
        
   
    if(child_pid != 0)
    {
        

    	printf("Parent : My process ID is : %u\n", getpid());
    	
        printf("Parent : The child process ID is : %u\n", child_pid);
        sleep(60);
        wait(NULL); 
        printf("Parent: The Parent has terminated");
       
    }

    else
    {
        
        printf("Child : My process ID is : %u\n", getpid());
    	
        printf("Child  : The parent process ID is : %u\n" , getppid());
        
    	int a;
        scanf("%d",&a);
        
       _Exit(EXIT_FAILURE); 	

        
       
    }
 
}
 
