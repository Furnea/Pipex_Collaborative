#include "../include/pipex.h"

int main(int argc, char **argv)
{
    if (argc < 5)
    {
        fprintf(stderr, "Usage: %s infile \"cmd1\" \"cmd2\" [\"cmd3\" ...] outfile\n", argv[0]);
        return 1;
    }

        // Bonus: n comandos
    procesar_linea(argc, argv);
    return 0;
}
