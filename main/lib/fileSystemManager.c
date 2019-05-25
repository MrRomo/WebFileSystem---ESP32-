
#include "fileSystemManager.h"

void fileSystemManager(message_t *req)
{
    printf("XQueue Received\n");
    printf("\n\nStart filesystem\n");

    struct dirent *entrada_directory;
    DIR *dr = NULL;
    FILE *archivo = NULL;
    char buff[100] = {0};
    // char *root = ;
    char * folder = req->folder;
    char file[25];
    // sprintf(folder, "%s/%s", root, req->folder);
    sprintf(file, "%s/%s", folder, req->file);
    printf("REQ File System %d\n", req->req);
    printf("REQ Folder System %s\n", req->folder);
    printf("FILE File System %s\n", file);
    printf("TEXT File System %s\n", req->text);
    printf("virtual file system [OK]\r\n");

    switch ((int)req->req)
    {
    case LIST:

        dr = opendir(req->folder);
        if (dr == NULL)
        {
            char *error = "no se encontró el directorio\r\n";
            printf("%s", error);
            xQueueSend(fileSystemRes, &error, portMAX_DELAY);
            break;
        }
        else
        {
            char *header = "*Listing files in folder: ";
            printf("%s %s*\n", header, folder);
            strcpy(buff, header);
            strcat(buff, "\n");
            while ((entrada_directory = readdir(dr)) != NULL)
            {
                char *dir = entrada_directory->d_name;
                strcat(buff, "--/");
                strcat(buff, dir);
                strcat(buff, "\n");
                printf("%s\r\n", buff);
            }
            printf("%s\r\n", buff);
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

    case CREATE:
        printf("*Creating file: %s*\n", file);
        dr = opendir(folder);
        archivo = fopen(file, "w");
        if (archivo != NULL)
        {
            //Escribir Archivo
            fprintf(archivo, req->text);
        }
        else
        {
            printf("ERROR CREATING FILE");
        }

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
