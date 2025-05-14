#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include "libft/libft.h"

int main(void)
{
	int fork;
	int fd;

	fd = open("test3.txt", O_RDWR);
	dup2(fd, 0);
	close(fd);
	char *arr[] = {"/usr/bin/cat", NULL};
	execve(arr[0], arr, 0);
}

