#include "commandLine.h"

message_t argsParser(char *str)
{

   // char str[80] = "cat /vsd/file.txt -m \"texto libre\" ";
   char *s = " ";
   char *token;
   char c = 0;
   message_t msg;
   msg.req = 0;
   msg.first_arg = "NULL";
   /* get the first token */
   token = strtok(str, s);
   msg.first_arg = token;
   /* walk through other tokens */
   while (token != NULL)
   {

      printf("C=%d %s\n", c, token);
      c++;
      if ((c == 2) && (token != NULL))
      {
         memset(msg.file, 0, sizeof(msg.file));
         strcpy(msg.file,token);
      }
      if(c==3){
         s = "\"";
      }  
      if ((c == 4) && (token != NULL))
      {
         memset(msg.text, 0, sizeof(msg.text));
         strcpy(msg.text,token);
      }
      token = strtok(NULL, s);
   }


   return msg;
}
void commandLine(char *req)
{
   message_t msg;
   msg = argsParser(req);
   if ((!strcmp(msg.first_arg, "ls\n")) || (!strcmp(msg.first_arg, "ls")))
   {
      msg.req = LIST;
   }
   else if (!strcmp(msg.first_arg, "cat"))
   {
      msg.req = CAT;
   }
   else if (!strcmp(msg.first_arg, "touch"))
   {
      msg.req = CREATE;
   }
   else if (!strcmp(msg.first_arg, "rm"))
   {
      msg.req = DELETE;
   }
   else if (!strcmp(msg.first_arg, "nano"))
   {
      msg.req = EDIT;
   }
   else if (!strcmp(msg.first_arg, "cd"))
   {
      msg.req = FOLDER;
   }
   else if (!strcmp(msg.first_arg, "mkdir"))
   {
      msg.req = CFOLDER;
   }


   xQueueSend(fileSystemReq, &msg, portMAX_DELAY);
}
