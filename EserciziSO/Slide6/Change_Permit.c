#include <stdio.h>
#include <sys/stat.h>
#include <sys/file.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>

void err_sys (const char* x)
{
	perror(x);
	exit(1);
}
int main(int argc, char *argv[])
{
	umask(0);
	if (creat("foo", S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP |S_IROTH| S_IWOTH)< 0 )
		err_sys("creat error for foo");

	umask(S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
	if (creat("bar", S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH) < 0)
		err_sys("creat error for bar");
		exit(0);
}