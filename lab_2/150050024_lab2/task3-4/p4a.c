#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <netdb.h>


int main(int argc, char const *argv[]){
    
    char* filePath = strdup(argv[1]);

    


    int fd = open(filePath, O_CREAT | O_WRONLY, S_IRUSR, S_IWUSR);


    int pid = fork();


    if(pid == 0){


        char * msg1 = (char*) "hello world! I am the child\n";
        write(fd, msg1, strlen(msg1));

        printf("Child %d: writing to file %d\n", getpid(), fd);
        close(fd);
    }
    else{

        printf("Parent: File opened. fd=%d.\n", fd);

        printf("Parent %d: writing to file %d\n", getpid(), fd);
        char * msg = (char*) "hello world! I am the parent\n";

        write(fd, msg, strlen(msg));
        int w;
        
        wait(&w);

        printf("Parent : The child has terminated.\n");
        close(fd);
    }

    return 0;
}