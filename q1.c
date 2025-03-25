#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

int main()
{
    // Open a file for writing (create if it doesn't exist)
    int fd = open("example.txt", O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    if (fd == -1)
    {
        perror("Error opening file");
        return 1;
    }

    // Fork to create a new process
    pid_t pid = fork();

    if (pid == -1)
    {
        perror("Fork failed");
        return 1;
    }

    if (pid == 0)
    {
        // Child process writing to the file
        const char *child_msg = " Child process writing.\n";
        if (write(fd, child_msg, 22) == -1)
        {
            perror("Error writing by child");
        }
        close(fd);
        return 0;
    }
    else
    {
        // Parent process writing to the file
        const char *parent_msg = " Parent process writing.\n";
        if (write(fd, parent_msg, 22) == -1)
        {
            perror("Error writing by parent");
        }
        close(fd);
        return 0;
    }
}
