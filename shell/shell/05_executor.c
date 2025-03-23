//Putting together builtins and processes
//The last missing piece of the puzzle is to implement lsh_execute(), the function that will either launch a builtin, or a process. If you’re reading this far, you’ll know that we’ve set ourselves up for a really simple function:
#include "file.h"
int lsh_execute(char **args)
{
  int i;

  if (args[0] == NULL) {
    // An empty command was entered.
    return 1;
  }

  for (i = 0; i < lsh_num_builtins(); i++) {
    if (strcmp(args[0], builtin_str[i]) == 0) {
      return (*builtin_func[i])(args);
    }
  }

  return lsh_launch(args);
}
//All this does is check if the command equals each builtin, and if so, run it. If it doesn’t match a builtin, it calls lsh_launch() to launch the process. The one caveat is that args might just contain NULL, if the user entered an empty string, or just whitespace. So, we need to check for that case at the beginning