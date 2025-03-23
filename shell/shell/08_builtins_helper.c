//Shell Builtins
//You may have noticed that the lsh_loop() function calls lsh_execute(), but above, we titled our function lsh_launch(). This was intentional! You see, most commands a shell executes are programs, but not all of them. Some of them are built right into the shell.

//The reason is actually pretty simple. If you want to change directory, you need to use the function chdir(). The thing is, the current directory is a property of a process. So, if you wrote a program called cd that changed directory, it would just change its own current directory, and then terminate. Its parent process’s current directory would be unchanged. Instead, the shell process itself needs to execute chdir(), so that its own current directory is updated. Then, when it launches child processes, they will inherit that directory too.

//Similarly, if there was a program named exit, it wouldn’t be able to exit the shell that called it. That command also needs to be built into the shell. Also, most shells are configured by running configuration scripts, like ~/.bashrc. Those scripts use commands that change the operation of the shell. These commands could only change the shell’s operation if they were implemented within the shell process itself.

//So, it makes sense that we need to add some commands to the shell itself. The ones I added to my shell are cd, exit, and help. Here are their function implementations below:

/*
  Function Declarations for builtin shell commands:
 */
#include "file.h"

/*
  List of builtin commands, followed by their corresponding functions.
 */

/*
  Builtin function implementations.
*/
int lsh_cd(char **args)
{
  if (args[1] == NULL) {
    fprintf(stderr, "lsh: expected argument to \"cd\"\n");
  } else {
    if (chdir(args[1]) != 0) {
      perror("lsh");
    }
  }
  return 1;
}

int lsh_help(char **args)
{
  int i;
  printf("Stephen Brennan's LSH\n");
  printf("Type program names and arguments, and hit enter.\n");
  printf("The following are built in:\n");

  for (i = 0; i < lsh_num_builtins(); i++) {
    printf("  %s\n", builtin_str[i]);
  }

  printf("Use the man command for information on other programs.\n");
  return 1;
}

int lsh_exit(char **args)
{
  return 0;
}
//There are three parts to this code. The first part contains forward declarations of my functions. A forward declaration is when you declare (but don’t define) something, so that you can use its name before you define it. The reason I do this is because lsh_help() uses the array of builtins, and the arrays contain lsh_help(). The cleanest way to break this dependency cycle is by forward declaration.

//The next part is an array of builtin command names, followed by an array of their corresponding functions. This is so that, in the future, builtin commands can be added simply by modifying these arrays, rather than editing a large “switch” statement somewhere in the code. If you’re confused by the declaration of builtin_func, that’s OK! I am too. It’s an array of function pointers (that take array of strings and return an int). Any declaration involving function pointers in C can get really complicated. I still look up how function pointers are declared myself!1

//Finally, I implement each function. The lsh_cd() function first checks that its second argument exists, and prints an error message if it doesn’t. Then, it calls chdir(), checks for errors, and returns. The help function prints a nice message and the names of all the builtins. And the exit function returns 0, as a signal for the command loop to terminate.