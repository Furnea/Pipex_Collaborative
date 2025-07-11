
#ifndef PIPEX_H
#define PIPEX_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <string.h>
# include <sys/wait.h>
# include <errno.h>

// pipex.c
void procesar_linea(int argc, char **argv);

// parser.c
char    **split(char *cmd);

// executor.c
void    execute_cmd(char *cmd);

// utils.c
void    error_exit(const char *msg);

#endif


