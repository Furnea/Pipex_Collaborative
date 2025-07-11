#include "../include/pipex.h"

// BONUS: n comandos REUTILIZADO del procesar linea del scripter (con cambios)
void procesar_linea(int argc, char **argv)
{
    int n_cmds = argc - 3;  // calcula cuantos comandos hay (restamos ./pipex, infile, outfile)
    int pipefd[n_cmds - 1][2]; //n-1 pipes
    //RECORDATORIO: los pipes son arrays de dos int -> 0 (lectura) y 1 escritura
    //FUNCIONAN ASI: comando -> pipefd[1] (escritura) -> pipefd[0] (lectura) -> comando2. uno escribe, el otro lo lee
    pid_t pid;
    int fd_in = open(argv[1], O_RDONLY); //abre con permiso lectura, guarda file descriptor
    int fd_out = open(argv[argc - 1], O_CREAT | O_WRONLY | O_TRUNC, 0644);

    if (fd_in < 0 || fd_out < 0)
        error_exit("bonus setup");

    // Crear pipes
    for (int i = 0; i < n_cmds - 1; i++) {
        if (pipe(pipefd[i]) == -1)
            error_exit("pipe error");
    }

    for (int i = 0; i < n_cmds; i++) //loop for each cmd
    {
        pid = fork(); //CHILD PROCESS for each cmd, independent process
        if (pid < 0) {
            perror("Error en fork");
            continue;
        }
        if (pid == 0)
        {
            // stdin
            if (i == 0) //primer comando lee de infile, los demas leen del pipe anterior
                dup2(fd_in, STDIN_FILENO);
            else
                dup2(pipefd[i - 1][0], STDIN_FILENO);

            // stdout
            if (i == n_cmds - 1) //ultimo comando escribe en outfile
                dup2(fd_out, STDOUT_FILENO);
            else
                dup2(pipefd[i][1], STDOUT_FILENO);

            //avoid zombie p
            for (int j = 0; j < n_cmds - 1; j++)
            {
                close(pipefd[j][0]);
                close(pipefd[j][1]);
            }

            close(fd_in); close(fd_out);
            execute_cmd(argv[2 + i]);  // cmd empieza en argv[2]
        }
    }

    //CLOSE PARENT -> recordatorio: primero todos los forks y luego cierra tofos los pipes
    close(fd_in); close(fd_out);
    for (int i = 0; i < n_cmds - 1; i++)
    {
        close(pipefd[i][0]);
        close(pipefd[i][1]);
    }

    //Esperar a que hijos acaben
    for (int i = 0; i < n_cmds; i++)
        wait(NULL);
} //es diferente al mio porque el mio tenia tb lo del background, ademas leia un fichero, no un comando
//tb esperaba a cada hijo antes de seguir y eso no es ejecucion paralela, aqui si hay paralelismo
//yo tengo las redirecciones aparte porque hay comandos con < >, aqui ya van implicadas en los dup2