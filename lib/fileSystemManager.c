#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"
#include "freertos/task.h"
#include "string.h"

#include "esp_system.h"
#include "esp_log.h"

#include "nvs_flash.h"
#include "esp_vfs.h"
#include "esp_vfs_fat.h"

// #include "dinamicVector.h"
#define LIST 1
#define FOLDER 2
#define CAT 3
#define CREATE 4
#define EDIT 5
#define DELETE 6


typedef struct message
{
    int req;
    void ** res;
    void ** filename;
    void ** folder;
    void ** text;

}message_t;


// void testFileSystem(esp_vfs_fat_mount_config_t mount_config)
// {
//     //Create file
//     message_t message;

//     message.request = vector_new(4);
//     message.response = vector_new(4);
//     char res[50] = {0};
//     vector_insert(message.request, 0, LIST); //TYPE OF REQUEST
//     vector_insert(message.request, 1, "test.txt");
//     vector_insert(message.request, 2, "/vsd");
//     vector_insert(message.request, 3, "Texto de prueba");
//     fileSystemManager(&message.request, mount_config);
    
//     // vector_insert(message.request, 0, DELETE);
//     // vector_insert(message.request, 2, "HISTORY.txt");
//     // fileSystemManager(message.request, mount_config);

//     // // vector_insert(message.request, 0, CREATE);
//     // // vector_insert(message.request, 2, "test2.txt");
//     // // fileSystemManager(message.request, mount_config);

//     // vector_insert(message.request, 0, LIST);
//     // fileSystemManager(message.request, mount_config);

//     // vector_insert(message.request, 0, CAT);
//     // vector_insert(message.request, 2, "test.txt");
//     // fileSystemManager(message.request, mount_config);

//     // vector_insert(message.request, 0, LIST);
//     // vector_insert(message.request, 2, "test.txt");
//     // fileSystemManager(message.request, mount_config);

//     // vector_insert(message.request, 0, DELETE);
//     // vector_insert(message.request, 2, "test2.txt");

//     // fileSystemManager(message, mount_config);
// }

void fileSystemManager(message_t * message, esp_vfs_fat_mount_config_t mount_config)
{

    printf("\n\nStart filesystem\n");
    char buff[50] = {0};
    char direction[80] = {0};

    // int req = (int *)vector_get(file_req, 0);
    // char *res = (char *)vector_get(file_req, 1);
    // char *filename = (char *)vector_get(file_req, 2);
    // char *folder = (char *)vector_get(file_req, 3);
    // char *text = (char *)vector_get(file_req, 4);


    // printf("req: %d - res: %s - filename: %s - text: %s\n", message->req, message->res, message->filename, message->text);
    // sprintf(direction, "%s/%s", folder, filename);

    //Inicialización NVS (Non Volatile Storage)
    DIR *dr = NULL;
    struct dirent *entrada_directory;
    FILE *archivo = NULL;

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
        char lectura[80];
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
        char dir[80] = {0};
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
