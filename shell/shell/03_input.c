//Reading a line
//Reading a line from stdin sounds so simple, but in C it can be a hassle. The sad thing is that you don’t know ahead of time how much text a user will enter into their shell. You can’t simply allocate a block and hope they don’t exceed it. Instead, you need to start with a block, and if they do exceed it, reallocate with more space. This is a common strategy in C, and we’ll use it to implement lsh_read_line().
#include "file.h"
#define LSH_RL_BUFSIZE 1024
char *lsh_read_line(void)
{
  int bufsize = LSH_RL_BUFSIZE;
  int position = 0;
  char *buffer = malloc(sizeof(char) * bufsize);
  int c;

  if (!buffer) {
    fprintf(stderr, "lsh: allocation error\n");
    exit(EXIT_FAILURE);
  }

  while (1) {
    // Read a character
    c = getchar();

    // If we hit EOF, replace it with a null character and return.
    if (c == EOF || c == '\n') {
      buffer[position] = '\0';
      return buffer;
    } else {
      buffer[position] = c;
    }
    position++;

    // If we have exceeded the buffer, reallocate.
    if (position >= bufsize) {
      bufsize += LSH_RL_BUFSIZE;
      buffer = realloc(buffer, bufsize);
      if (!buffer) {
        fprintf(stderr, "lsh: allocation error\n");
        exit(EXIT_FAILURE);
      }
    }
  }
}
//The first part is a lot of declarations. If you hadn’t noticed, I prefer to keep the old C style of declaring variables before the rest of the code. The meat of the function is within the (apparently infinite) while (1) loop. In the loop, we read a character (and store it as an int, not a char, that’s important! EOF is an integer, not a character, and if you want to check for it, you need to use an int. This is a common beginner C mistake.). If it’s the newline, or EOF, we null terminate our current string and return it. Otherwise, we add the character to our existing string.

//Next, we see whether the next character will go outside of our current buffer size. If so, we reallocate our buffer (checking for allocation errors) before continuing. And that’s really it.

//Those who are intimately familiar with newer versions of the C library may note that there is a getline() function in stdio.h that does most of the work we just implemented. To be completely honest, I didn’t know it existed until after I wrote this code. This function was a GNU extension to the C library until 2008, when it was added to the specification, so most modern Unixes should have it now. I’m leaving my existing code the way it is, and I encourage people to learn it this way first before using getline. You’d be robbing yourself of a learning opportunity if you didn’t! Anyhow, with getline, the function becomes easier:
/*
char *lsh_read_line(void)
{
  char *line = NULL;
  ssize_t bufsize = 0; // have getline allocate a buffer for us

  if (getline(&line, &bufsize, stdin) == -1){
    if (feof(stdin)) {
      exit(EXIT_SUCCESS);  // We recieved an EOF
    } else  {
      perror("readline");
      exit(EXIT_FAILURE);
    }
  }

  return line;
}
*/
//This is not 100% trivial because we still need to check for EOF or errors while reading. EOF (end of file) means that either we were reading commands from a text file which we’ve reached the end of, or the user typed Ctrl-D, which signals end-of-file. Either way, it means we should exit successfully, and if any other error occurs, we should fail after printing the error.