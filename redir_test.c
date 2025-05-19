#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include "libft/libft.h"

int main(void)
{
	int fork;
	int fd;

	fd = open("stdout.txt", O_RDWR);
	dup2(fd, 1);
	close(fd);
	char *arr[] = {"/usr/bin/echo", "hello0000000000000\n" , NULL};
	execve(arr[0], arr, 0);
}

