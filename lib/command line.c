#include <string.h>
#include <stdio.h>

int main () {
   char str[80] = "cat /vsd/file.txt -m \"texto libre\" ";
   char *s = " ";
   char *token;
   char c = 0;
   /* get the first token */
   token = strtok(str, s);
   
   /* walk through other tokens */
   while( token != NULL ) {
      printf( " %s\n", token );
      c++;
      if(c==3){
          s = "\"";
      }

      token = strtok(NULL, s);
   }
   
   return(0);
}