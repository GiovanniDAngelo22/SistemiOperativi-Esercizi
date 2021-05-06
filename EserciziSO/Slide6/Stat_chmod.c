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
	struct  stat statbuf;
	umask(0);
	if (chmod("bar", S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)< 0 )
		err_sys("chmod error for bar");
	if (stat("foo",&statbuf) <0)
		err_sys("stat error for foo");
	if (chmod("foo", (statbuf.st_mode & ~S_IXGRP) | S_ISGID) < 0)
		err_sys("chmod error for foo");
		exit(0);
}