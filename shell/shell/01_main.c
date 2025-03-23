//Basic lifetime of a shell
//Let’s look at a shell from the top down. A shell does three main things in its lifetime.

//Initialize: In this step, a typical shell would read and execute its configuration files. These change aspects of the shell’s behavior.
//Interpret: Next, the shell reads commands from stdin (which could be interactive, or a file) and executes them.
//Terminate: After its commands are executed, the shell executes any shutdown commands, frees up any memory, and terminates.
//These steps are so general that they could apply to many programs, but we’re going to use them for the basis for our shell. Our shell will be so simple that there won’t be any configuration files, and there won’t be any shutdown command. So, we’ll just call the looping function and then terminate. But in terms of architecture, it’s important to keep in mind that the lifetime of the program is more than just looping.
#include "file.h"
int main(int argc, char **argv)
{
  // Load config files, if any.

  // Run command loop.
  lsh_loop();

  // Perform any shutdown/cleanup.

  return EXIT_SUCCESS;
}
//Here you can see that I just came up with a function, lsh_loop(), that will loop, interpreting commands. We’ll see the implementation of that next.

