
#include "fileSystemManager.h"

void fileSystemManager(message_t *req)
{
    printf("XQueue Received\n");
    printf("\n\nStart filesystem\n");

    struct dirent *entrada_directory;
    DIR *dr = NULL;
    FILE *archivo = NULL;
    char buff[50] = {0};
    char *folder = "/vsd";
    char file [25];
    sprintf(file, "%s/%s",folder,req->file);
    

    printf("REQ File System %d\n", req->req);
    printf("FILE File System %s\n", file);
    printf("TEXT File System %s\n", req->text);
    printf("virtual file system [OK]\r\n");

    // dr = opendir("/vsd");

    switch ((int)req->req)
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
        printf("*Open file: %s*\n", file);

        dr = opendir(folder);
        archivo = fopen(file, "r");
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
        printf("*Creating file: %s*\n", file);
        dr = opendir(folder);
        archivo = fopen(file, "w");
        if (archivo != NULL)
        {
            //Escribir Archivo
            fprintf(archivo, req->text);
        }else
        {
            printf("ERROR CREATING FILE");
        }
        

        break;
    case EDIT:

        break;
    case DELETE:
        printf("*Deleting file: %s*\n", file);

        int status = remove(file);

        if (status == 0)
            printf("%s file deleted successfully.\n", file);
        else
        {
            printf("Unable to delete the file\n");
            perror("Following error occurred");
        }
        break;

    default:
        printf("req not found");
        break;
    }
    fclose(archivo);
}
