
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{

    printf("hello (pid:%d)\n", (int)getpid()); // the id of the parent
    int rc = fork();
    //Parent process: fork() returns the PID of the child to the parent.
   //Child process: fork() returns 0 to the child.

    if (rc < 0)
    {

        // fork failed
        fprintf(stderr, "fork failed\n");
        exit(1);
    }
    else if (rc == 0)
    {
        // child (new process)
        printf("child (pid:%d)\n", (int)getpid());
    }
        //Parent Process: After the fork(), the parent will have rc set to the PID of the child. So, it will enter the else part of your code (because rc > 0).
        //Child Process: The child process will have rc set to 0. So, it will enter the else if (rc == 0) part of the code.
    else
    {
        // parent goes down this path (main) printf("parent of %d (pid:%d)\n",
        printf("parent of %d is (pid:%d)\n",
               rc, (int)getpid());
    }
    return 0;
}
/*Let us understand what happened in more detail in calling_fork.c. When it first started running, the process prints out a hello message; included in that message is its process identifier, also known as a PID. The process has a PID of 21790(differnt with each machin); in UNIX systems, the PID is used to name the process if one wants to do something with the process, such as (for example) stop it from running. So far, so good.
Now the interesting part begins. The process calls the fork() system call, which the OS provides as a way to create a new process. The odd part: the process that is created is an (almost) exact copy of the calling process. That means that to the OS, it now looks like there are two copies of the program calling_fork.c running, and both are about to return from the fork() system call. The newly-created process (called the child, in contrast to the creating parent) doesn’t start running at main(), like you might expect (note, the “hello” message only got printed out once); rather, it just comes into life as if it had called fork() itself.*/