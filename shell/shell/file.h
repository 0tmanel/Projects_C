#ifndef FILE_H
#define FILE_H
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
int lsh_cd(char **args);
int lsh_help(char **args);
int lsh_exit(char **args);
void lsh_loop(void);
int lsh_launch(char **args);
char *lsh_read_line(void);
char **lsh_split_line(char *line);
int lsh_execute(char **args);
extern char *builtin_str[];
extern int (*builtin_func[]) (char **);
extern int lsh_num_builtins();

#endif