#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define  BUFF_SIZE   1024


typedef struct{
   char *USER;
   int PID;
   double CPU;
   double mem;
}PS;

PS *get_cpu_pid()
{
   char  *temp, **buff, temp_USER[BUFF_SIZE];
   int size=0, size1=0, loop, temp_PID;
   double temp_CPU, temp_mem; 
   FILE *fp;
   PS *myinfo;

   fp = popen( "ps aux --sort=-pcpu,pid", "r");
   if ( NULL == fp)
   {
      perror( "popen() 실패");
      return -1;
   }
   
   while(1)
   {
      fgets(temp,BUFF_SIZE,fp);
      if(feof!=0)
         break;
      size++;
   }
   
   buff=(char**)malloc(size*sizeof(char*));
  
   fseek(fp,0L,SEEK_SET);

   for(loop=0;loop<size;loop++)
   {
      fgets(temp, BUFF_SIZE, fp);
      buff[loop]=(char*)malloc((strlen(temp)+1)*sizeof(char));
      strcpy(buff[loop],temp);
      printf( "%s", buff);
   }

   for(loop=0;loop<size;loop++)
   {
      sscanf(buff[loop],"%s",temp_USER);
      if(strcmp(temp_USER,"USER")==0 || strcmp(temp_USER,"root") || temp_CPU==0)
         continue;
      size1++;
   }

   myinfo=(PS*)malloc(size1*sizeof(PS));

   for(loop=0;loop<size1;loop++)
   {
      sscanf(buff[loop],"%s%d%lf%lf",temp_USER,&temp_PID,&temp_CPU,&temp_mem);
      if(strcmp(temp_USER,"USER")==0 || strcmp(temp_USER,"root") || temp_CPU==0)
         continue;
      myinfo[loop].USER = (char*)malloc((strlen(temp_USER)+1)*sizeof(char));
      strcpy(myinfo[loop].USER,temp_USER);
      myinfo[loop].PID=temp_PID;
      myinfo[loop].CPU=temp_CPU;
      myinfo[loop].mem=temp_mem;
   }
   
   pclose(fp);

   return myinfo;
} 
