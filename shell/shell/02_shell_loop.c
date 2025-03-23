/*
Basic loop of a shell

So we’ve taken care of how the program should start up. Now, for the basic program logic: what does the shell do during its loop? Well, a simple way to handle commands is with three steps:

//Read: Read the command from standard input.
//Parse: Separate the command string into a program and arguments.
Execute: Run the parsed command.
Here, I’ll translate those ideas into code for lsh_loop():
*/
#include "file.h"
void lsh_loop(void)
{
  char *line;
  char **args;
  int status;

  do {
    printf("> ");
    line = lsh_read_line();
    args = lsh_split_line(line);
    status = lsh_execute(args);

    free(line);
    free(args);
  } while (status);
}
//Let’s walk through the code. The first few lines are just declarations. The do-while loop is more convenient for checking the status variable, because it executes once before checking its value. Within the loop, we print a prompt, call a function to read a line, call a function to split the line into args, and execute the args. Finally, we free the line and arguments that we created earlier. Note that we’re using a status variable returned by lsh_execute() to determine when to exit.