#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int ac, char **av, char **envp)
{
	int	pork[2];
	int pork2;
	int	pipe_fd[2];

	char *array[] = {"/usr/bin/echo", "Hello", NULL};
	char *array2[] = {"/usr/bin/cat", "-e", NULL};

	memset(&pork, 0, sizeof(int[2]));
	if (pipe(pipe_fd) < 0)
		perror("pipe failed\n");
	pork[0] = fork();
	if (pork[0] == 0)
	{
		dup2(pipe_fd[1], 1);
		close(pipe_fd[1]);
		close(pipe_fd[0]);
		execve(array[0], array, envp);
	}

	pork[1] = fork();
	if (pork[1] == 0)
	{
		dup2(pipe_fd[0], 0);
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		execve(array2[0], array2, envp);
	}
	close(pipe_fd[1]);
	close(pipe_fd[0]);
	waitpid(pork[0], NULL, 0);
	waitpid(pork[1], NULL, 0);
	printf("Done bro\n");
}
