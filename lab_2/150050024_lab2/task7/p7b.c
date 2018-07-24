#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <stdio.h>


int main(int argc, char *argv[]){

    int n = atoi(argv[1]);
    int a[n];
    for(int i=0;i<n;i++) 
    {   

        if(fork() == 0)
        {   
            if(i == 0){
            printf("Parent is %d\n" ,getppid());
        }
            printf("Child %d is created\n",getpid());
            a[i] = getpid();
            exit(0);
        }
    }
    for(int i=0;i<n;i++) 
    wait(NULL);
    
    printf("%d", a[4]);

}
