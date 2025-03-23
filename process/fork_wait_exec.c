#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
int main(int argc, char *argv[])
{

    printf("hello (pid:%d)\n", (int)getpid());
    int rc = fork();
    if (rc < 0)
    { // fork failed; exit
        fprintf(stderr, "fork failed\n");
        exit(1);
    }
    else if (rc == 0)
    { // child (new process)
        printf("child (pid:%d)\n", (int)getpid());
        char *myargs[3];
        myargs[0] = strdup("wc");   // program: "wc"
        myargs[1] = strdup("calling_fork.c"); // arg:
        myargs[2] = NULL;           // mark
        execvp(myargs[0], myargs);  // runs
        printf("this shouldn't print out");
    }
    else
    { // parent goes down this path
        int rc_wait = wait(NULL);
        printf("parent of %d (rc_wait:%d) (pid:%d)\n",
               rc, rc_wait, (int)getpid());
    }
    return 0;
}
/*
What it does: given the name of an executable (e.g., wc), and some arguments (e.g., calling_fork.c), it loads code (and static data) from that executable and overwrites its current code segment (and current static data) with it; the heap and stack and other parts of the memory space of the program are re-initialized. Then the OS simply runs that program, passing in any arguments as the argv of that process. Thus, it does not create a new process; rather, it transforms the currently running program (formerly fork_wait_exec.c) into a different running program (wc). After the exec() in the child, it is almost as if fork_wait_exec.c never ran; a successful call to exec() never returns.*/