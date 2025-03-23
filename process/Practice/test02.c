//Write another program using fork(). The child process should print “hello”; the parent process should print “goodbye”. You should try to ensure that the child process always prints first; can you do this without calling wait() in the parent?
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sched.h>
int main ()
{
    int rc = fork();
    if(rc < 0)
    {
        printf("fork faild.");
        return -1;
    }
    else if (rc == 0)
    {
        printf("hello\n");
    }
    else{
        //You can use sched_yield() to hint the operating system to let another process (in this case, the child) run. This doesn't guarantee the child will run first, but it might increase the chances.
         sched_yield();
        printf("goodbey\n");
    }
    return 0;
}