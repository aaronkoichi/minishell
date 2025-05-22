#include "exec/execute.h"
#include <fcntl.h>

int	main(void)
{
	int	pork;
	int	fd;

	pork = fork();
	if (pork == 0)
	{
		char *arr[] = {"/usr/bin/echo", "hello0000000000000\n" , NULL};
		fd = open("hello.txt", O_CREAT | O_RDWR | O_APPEND, 0644);
		if (fd < 0)
			perror("lol\n");
		else
		{
			dup2(fd, 1);
			// close(fd);
			execve(arr[0], arr, 0);
		}
	}
}
