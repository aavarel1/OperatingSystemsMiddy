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
        close(STDOUT_FILENO);
        printf("This will NOT be printed to the terminal.\n");
        write(STDOUT_FILENO, "This will also NOT be printed.\n", 30);
    } else {
        printf("This is from the parent process.\n");
    }
    return 0;
}

// if the child process tries to write to stdout it will fail silently and no output will be printed

