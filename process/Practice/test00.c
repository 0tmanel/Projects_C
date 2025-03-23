//Writeaprogramthatcallsfork().Beforecallingfork(),havethe main process access a variable (e.g., x) and set its value to some- thing (e.g., 100). What value is the variable in the child process? What happens to the variable when both the child and parent change the value of x?

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>
int main ()
{
    int x = 100;
    
    printf("value here in the parent is %d, the id is %d\n", x, (int)getpid());
    int rc = fork();
    if(rc < 0)
    {
        return 1;
    }
    else if(rc == 0)
    {
        printf("value here in the child is %d, the id is %d\n", x, (int)getpid());
       x = 6;
    printf("%d\n (id: %d)", x, (int)getpid());
    }
    x = 9;
     printf("%d\n (id: %d)", x, (int)getpid());
}