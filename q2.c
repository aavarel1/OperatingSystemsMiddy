#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

int main()
{
    int fd = open("example.txt", O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    if (fd == -1)
    {
        perror("Error opening file");
        return 1;
    }

    pid_t pid = fork();

    if (pid == -1)
    {
        perror("Fork failed");
        return 1;
    }

    if (pid == 0)
    {
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
        const char *parent_msg = " Parent process writing.\n";
        if (write(fd, parent_msg, 22) == -1)
        {
            perror("Error writing by parent");
        }
        close(fd);
        return 0;
    }
}

// both the parent and child processes can access the file descriptor returned by open()
// when both the parent and child are writing at the same time the output is interleaved