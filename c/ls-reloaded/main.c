#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>


int main(int argc, char* argv[])
{
    if(argc != 2)
    {
        fprintf(stderr, "Syntaxe incorrecte.\n");
        exit(EXIT_FAILURE);
    }

    DIR* repertoire;

    if( (repertoire = opendir(argv[1])) != NULL)
    {
        chdir(argv[1]);

            struct dirent* input = NULL;
            struct stat buffer;
            struct passwd *dataUser = NULL;
            struct group *dataGrp = NULL;
            char bufferDate[20];
            char c;

            while(input = readdir(repertoire))
            {
              stat(input->d_name, &buffer);
              dataUser = getpwuid(buffer.st_uid);
              dataGrp = getgrgid(buffer.st_gid);
              strftime(bufferDate, 20, "%d/%m/%Y", localtime(&buffer.st_mtim));
              c = (S_ISDIR(buffer.st_mode) ? 'd':'f');

              printf("%d %c %6o %d %s %s %4d %s ",
                     buffer.st_ino, c, buffer.st_mode & 0777,
                     buffer.st_nlink, dataUser->pw_gecos, dataGrp->gr_name,
                     buffer.st_size, bufferDate);
              printf("%s\n", input->d_name);
            }
    }
    else
    {
        fprintf(stderr, "Impossible d'acceder au repertoire specifie.\n");
        exit(EXIT_FAILURE);
    }

    printf("\n");
    return 0;
}
