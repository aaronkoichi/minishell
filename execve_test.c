#include "exec/execute.h"
#include <stdio.h>
#include <unistd.h>
#include "libft/libft.h"

void	free_charchar(char **yes)
{
	int i;

	i = 0;
	while(yes[i])
	{
		free(yes[i]);
		i++;
	}
	free(yes[i]);
	free(yes);
}

char **cmd_creator(int ac, char **av)
{
	char	**cmd;
	int		i;

	i = 0;
	cmd = malloc((ac) * sizeof(char *));
	if (!cmd)
		return (NULL);
	while ((ac - i - 1) != 0)
	{
		cmd[i] = ft_strdup(av[i + 1]);
		i++;
	}
	cmd[i] = NULL;
	return (cmd);
}

int main(int ac, char **av, char **envp)
{
	int	i;

	i = 0;
	char **cmd = cmd_creator(ac, av);
	if (access(cmd[0], X_OK | F_OK) == 0)
		execve(cmd[0],cmd, envp);
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH", 4) == 0)
			break ;
		else
			i++;
	}
	char **path = ft_split(envp[i] + 5, ':');
	i = 0;
	char *temp = ft_strjoin("/", cmd[0]);
	free(cmd[0]);
	cmd[0] = temp;
	while (path[i])
	{
		char *newpath = ft_strjoin(path[i], cmd[0]);
		if (access(newpath, F_OK | X_OK) == 0)
		{
			free(cmd[0]);
			cmd[0] = newpath;
			free_charchar(path);
			int pid = fork();
			if (pid == 0)
				execve(cmd[0], cmd, envp);
			waitpid(pid, NULL, 0);
			free_charchar(cmd);
			exit(0);
		}
		else
		{
			free(newpath);
			newpath = NULL;
			i++;
		}
	}
	free_charchar(cmd);
	free_charchar(path);
}
