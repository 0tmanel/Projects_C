//Write a program that opens a file (with the open() system call) and then calls fork() to create a new process. Can both the child and parent access the file descriptor returned by open()? What happens when they are writing to the file concurrently, i.e., at the same time?
  

//try to avoid looking at it the code , and try do it by yourself





















#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>

int main (int argc, char**av)
{
    int fd = open("file.txt", O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);

    int rc = fork();
    if(rc < 0)
    {
        write(1, "fork failed", 1);
        return -1;
    }
    else if(rc == 0)
    {
        const char *data = "Hello, World! i am child\n";
        write(fd, data, strlen(data));
      
    }
    else{
        int rc_wait = wait(NULL);
        const char *data2 = "Hello, World! i am parent\n";
        write(fd, data2, strlen(data2));
        close(fd);
    }

    return 0;

}
/*Initial File Offset: When the parent opens the file, the file descriptor points to the beginning of the file (offset 0).

Fork: After fork(), both processes (parent and child) share the same file descriptor. The file offset remains the same for both processes.

Writing from Both Processes:

If both processes attempt to write concurrently (which could happen in an interleaved manner), they will both write starting from the current file offset.
Since both processes are writing to the same file, the writes could overwrite or corrupt each other's data.*/