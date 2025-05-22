#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/wait.h>

void	execute_cmd(int out_fd)
{
	int fd;

	fd = open("stdin.txt", O_RDWR);
	int fd2 = open ("stdin2.txt", O_RDWR);
	char *arr[] = {"/usr/bin/cat", NULL};

	pid_t pork = fork();
	
	dup2(out_fd, 1);
	close(out_fd);
	if (pork == 0)
	{
		dup2(fd, 0);
		close(fd);
		execve(arr[0], arr, 0);
	}

	pid_t pork2 = fork();

	if (pork2 == 0)
	{
		dup2(fd2, 0);
		close(fd2);
		execve(arr[0], arr, 0);
	}
	close(fd);
	close(fd2);
	waitpid(pork, NULL, 0);
	waitpid(pork2, NULL, 0);
}

int main(void)
{
	int file = open("test1.txt", O_RDWR);
	int file2 = open("test2.txt", O_APPEND | O_RDWR);

	execute_cmd(file);
	execute_cmd(file2);
}

