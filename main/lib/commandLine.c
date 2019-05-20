#include "commandLine.h"

message_t argsParser(char *str)
{

   // char str[80] = "cat /vsd/file.txt -m \"texto libre\" ";
   char *s = " ";
   char *token;
   char c = 0;
   message_t msg;
   msg.req = "NULL";
   msg.filename = "NULL";
   msg.folder = "NULL";
   msg.text = "NULL";
   /* get the first token */
   token = strtok(str, s);
   msg.req = token;

   /* walk through other tokens */
   while (token != NULL)

   {
      
      printf("C=%d %s\n", c, token);
      c++;
      if (c == 3)
      {
         s = "\"";
      }
      if (c == 4)
      {
         msg.text = token;
      }
      if (c == 2)
      {
         msg.folder = token;
      }
      token = strtok(NULL, s);
   }
   printf("FOLDER: %s\n", msg.folder);
   if (c > 1)
   {
      s = "/";
      c = 0;
      char temp [50] = {0};
      strcpy(temp, msg.folder);  
      printf("FOLDER TEMP : %s\n", temp);
      token = strtok(temp, s);
      while (token != NULL)
      {
         printf("C=%d %s\n", c, token);
         strcpy(&msg.filename,token);  
         c++;
         token = strtok(NULL, s);
      }
   }

   return msg;
}
void commandLine(char *req)
{
   message_t msg;
   msg = argsParser(req);
   printf("REQ PARSER %s\n", msg.req);
   printf("FOLDER PARSER %s\n", msg.folder);
   printf("TEXT PARSER %s\n", msg.text);
   printf("FILENAME PARSER %s\n", msg.filename);
   // if (!strcmp(req, "ls\n"))
   // {
   //    req = LIST;
   //    printf("LIST files req \n");
   //    xQueueSend(fileSystemReq, &req, portMAX_DELAY);
   // }
   // else if (!strcmp(req, "cat\n"))
   // {
   //    req = CAT;
   //    printf("cat files req \n");
   //    xQueueSend(fileSystemReq, &req, portMAX_DELAY);
   // }
   // else if (!strcmp(req, "touch\n"))
   // {
   //    req = CREATE;
   //    printf("cat files req \n");
   //    xQueueSend(fileSystemReq, &req, portMAX_DELAY);
   // }
   // else if (!strcmp(req, "rm\n"))
   // {
   //    req = DELETE;
   //    printf("cat files req \n");
   //    xQueueSend(fileSystemReq, &req, portMAX_DELAY);
   // }
}
