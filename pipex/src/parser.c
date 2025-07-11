//
// Created by nicola on 08/07/2025.
//

#include "../include/pipex.h"
char **split(char *linea) { //reutilizado de la funcion tokenizar del scripter
    char **tokens = malloc(sizeof(char *) * 64); //hasta 63 args
    if (!tokens)
        return NULL;
    int i = 0;
    char *token = strtok(linea, " "); /* para recorrer cada palabra*/
    while (token) { /* loop to get through all words*/
        tokens[i++] = token;
        token = strtok(NULL, " "); /*le pasamos null para seguir desde donde se quedó*/
    }
    tokens[i] = NULL; /* marca el final del array porque execvp() lo pide*/
    return tokens; /*return the number of tokens*/
}
