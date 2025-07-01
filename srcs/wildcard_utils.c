/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlee <zlee@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 20:34:53 by zlee              #+#    #+#             */
/*   Updated: 2025/07/01 21:42:48 by zlee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

void	free_array(char **arr)
{
	int	i;

	i = -1;
	while(arr[++i])
	{
		free(arr[i]);
	}
	free(arr[i]);
	free(arr);
}

int	count_trim_lines(char **arr, const char *filename)
{
	int	c;
	int	i;

	c = 0;
	i = 0;
	if (filename[0] == '*')
		c++;
	while(arr[i])
		c += ft_strlen(arr[i++]) + 1;
	if (filename[ft_strlen(filename) - 1] != '*')
		c--;
	return (c);
}

void	ft_lstaddback_file(t_file **file, char *string)
{
	t_file	*head;

	head = *file;
	if (*file == NULL)
	{
		*file = malloc(sizeof(t_file));
		(*file)->file = ft_strdup(string);
		(*file)->next = NULL;
	}
	else
	{
		while (*file)
			file = &(*file)->next;
		*file = malloc(sizeof(t_file));
		(*file)->file = ft_strdup(string);
		(*file)->next = NULL;
		file = &head;
	}
}

void	ft_lstclear_file(t_file **file, void (*del)(void *))
{
	t_file	*temp;

	temp = NULL;
	if (!file || !del)
		return ;
	while (*file)
	{
		del((*file)->file);
		temp = (*file)->next;
		free(*file);
		*file = temp;
	}
}

int	ft_lstsize_file(t_file *file)
{
	int	c;

	c = 0;
	while (file)
	{
		c++;
		file = file->next;
	}
	return (c);
}


