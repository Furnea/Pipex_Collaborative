//
// Created by nicola on 08/07/2025.
//
#include "../include/pipex.h"

void error_exit(const char *msg)
{
    perror(msg);
    exit(EXIT_FAILURE);
}
