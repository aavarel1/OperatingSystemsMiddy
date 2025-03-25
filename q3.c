#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    pid_t pid = fork();  

    if (pid == -1) {
        perror("Fork failed");
        return 1;
    }

    if (pid == 0) {
        printf("hello\n");
    } else {
        sleep(1);  
        printf("goodbye\n");
    }

    return 0;
} 

// it is possible for the child process to print "hello" before the parent process prints "goodbye" without calling the wait() function or sleep() function
// you can do this by using file descriptors like pipe()
