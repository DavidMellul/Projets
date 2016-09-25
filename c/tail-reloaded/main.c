#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

int main(int argc, char* argv[])
{
    if(argc != 2)
    {
        fprintf(stderr, "Syntaxe incorrecte.\n");
        exit(EXIT_FAILURE);
    }

    int processus;

    if( (processus =  open(argv[1], O_RDONLY)) != -1)
    {
        int n = 0;
        char c;

        while(read(processus, &c, 1) != 0)
            n++;

        printf("Nombre de caracteres : %d\n", n);

        if(n < 30)
        {
            fprintf(stderr, "Le fichier specifie contient moins de 30 caracteres.\n");
        }
        else
        {
            lseek(processus, n - 30, SEEK_SET);
            int i = 0;
            for( i = 0; i < 30 ; i++)
            {
                read(processus, &c, 1);
                fprintf(stdout, "%c", c);
            }
        }
        close(processus);
    }
    else
    {
        fprintf(stderr, "Impossible d'acceder au fichier specifie.\n");
    }

    printf("\n");
    return EXIT_SUCCESS;
}
