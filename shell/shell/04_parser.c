//Parsing the line
//OK, so if we look back at the loop, we see that we now have implemented lsh_read_line(), and we have the line of input. Now, we need to parse that line into a list of arguments. I’m going to make a glaring simplification here, and say that we won’t allow quoting or backslash escaping in our command line arguments. Instead, we will simply use whitespace to separate arguments from each other. So the command echo "this message" would not call echo with a single argument this message, but rather it would call echo with two arguments: "this and message".

//With those simplifications, all we need to do is “tokenize” the string using whitespace as delimiters. That means we can break out the classic library function strtok to do some of the dirty work for us.
#include "file.h"
#define LSH_TOK_BUFSIZE 64
#define LSH_TOK_DELIM " \t\r\n\a"
char **lsh_split_line(char *line)
{
  int bufsize = LSH_TOK_BUFSIZE, position = 0;
  char **tokens = malloc(bufsize * sizeof(char*));
  char *token;

  if (!tokens) {
    fprintf(stderr, "lsh: allocation error\n");
    exit(EXIT_FAILURE);
  }

  token = strtok(line, LSH_TOK_DELIM);
  while (token != NULL) {
    tokens[position] = token;
    position++;

    if (position >= bufsize) {
      bufsize += LSH_TOK_BUFSIZE;
      tokens = realloc(tokens, bufsize * sizeof(char*));
      if (!tokens) {
        fprintf(stderr, "lsh: allocation error\n");
        exit(EXIT_FAILURE);
      }
    }

    token = strtok(NULL, LSH_TOK_DELIM);
  }
  tokens[position] = NULL;
  return tokens;
}
//If this code looks suspiciously similar to lsh_read_line(), it’s because it is! We are using the same strategy of having a buffer and dynamically expanding it. But this time, we’re doing it with a null-terminated array of pointers instead of a null-terminated array of characters.

//At the start of the function, we begin tokenizing by calling strtok. It returns a pointer to the first token. What strtok() actually does is return pointers to within the string you give it, and place \0 bytes at the end of each token. We store each pointer in an array (buffer) of character pointers.

//Finally, we reallocate the array of pointers if necessary. The process repeats until no token is returned by strtok, at which point we null-terminate the list of tokens.

//So, once all is said and done, we have an array of tokens, ready to execute. Which begs the question, how do we do that?