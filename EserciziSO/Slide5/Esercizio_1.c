#include <stdio.h>
#include <sys/file.h>
#include <unistd.h>
#include <stdlib.h>

int main(void)
{
   char in_buff[3], out_buff[11];

   while (1)
   {
   	read(STDIN_FILENO, in_buff,2);
   	out_buff[0]=in_buff[0]+in_buff[1];
   	write(STDOUT_FILENO, out_buff,11);
   	
   }
   return 0;
}