
#include "fileSystemManager.h"

void fileSystemManager(char req)
{
    printf("\n\nStart filesystem\n");
    struct dirent *entrada_directory;
    DIR *dr = NULL;
    FILE *archivo = NULL;
    char direction[80] = {0};
    char buff[50] = {0};

    char *folder = "/vsd";
    char *text = "texto de  prueba";
    char *filename = "test.txt";

    sprintf(direction, "%s/%s", folder, filename);

    printf("virtual file system [OK]\r\n");
    dr = opendir("/vsd");

    printf("XQueue Received");

    switch (req)
    {
    case LIST:
        printf("*Listing files in folder: %s*\n", folder);
        dr = opendir(folder);
        if (dr == NULL)
        {
            printf("no se encontró el directorio\r\n");
        }
        else
        {
            while ((entrada_directory = readdir(dr)) != NULL)
            {
                printf("%s\r\n", entrada_directory->d_name);
            }
            closedir(dr);
        }

        break;
    case CAT:
        printf("*Open file: %s*\n", filename);

        dr = opendir(folder);
        archivo = fopen(direction, "r");
        if (archivo != NULL)
        {
            fgets(buff, sizeof(buff), archivo);
            printf("%s\r\n", buff);
        }
        else
        {
            printf("ERROR Open File\n");
        }

        break;

    case FOLDER:

        break;

    case CREATE:
        printf("*Creating file: %s*\n", filename);
        dr = opendir(folder);
        archivo = fopen(direction, "w");
        if (archivo != NULL)
        {
            //Escribir Archivo
            fprintf(archivo, text);
        }

        break;
    case EDIT:

        break;
    case DELETE:
        printf("*Deleting file: %s*\n", direction);

        int status = remove(direction);

        if (status == 0)
            printf("%s file deleted successfully.\n", filename);
        else
        {
            printf("Unable to delete the file\n");
            perror("Following error occurred");
        }
        break;

    default:
        break;
    }
    fclose(archivo);
}
