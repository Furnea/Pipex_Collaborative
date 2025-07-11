//
// Created by nicola on 08/07/2025.
//
#include "../include/pipex.h"

void execute_cmd(char *cmd)
{
    char **args = split(cmd);
    if (!args)
        error_exit("split");

    execvp(args[0], args);
    perror("fallo"); // si falla
    exit(1);
}
