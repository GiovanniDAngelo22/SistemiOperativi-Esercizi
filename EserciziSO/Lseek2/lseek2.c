#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "apue.h"

char buf1[] = "abcdefghij";
char buf2[] = "ABCDEFGHIJ";
int main(void) {
int fd;
if ( (fd = creat("file.hole", FILE_MODE)) < 0)
err_sys("creat error");
if (write(fd, buf1, 10) != 10) err_sys("buf1 write error");
/* offset ora = 10 */
if (lseek(fd, 40, SEEK_SET) == -1) err_sys("lseek error");
/* offset ora = 40 */
if (write(fd, buf2, 10) != 10) err_sys("buf2 write error");
/* offset ora = 50 */
exit(0);
}