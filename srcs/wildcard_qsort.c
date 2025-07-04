/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_qsort.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlee <zlee@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 21:37:25 by zlee              #+#    #+#             */
/*   Updated: 2025/07/05 01:03:25 by zlee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

int	arr_size(char **arr)
{
	size_t	i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}

size_t partition(char **arr, int low, int high)
{
	char	*pivot;
	char	*temp;
	int		i;
	int		j;

	i = low - 1;
	j = low;
	pivot = arr[high];
	while (j < high)
	{
		if (ft_strcmp(arr[j], pivot) < 0)
		{
			i++;
			temp = arr[i];
			arr[i] = arr[j];
			arr[j] = temp;
		}
		j++;
	}
	temp = arr[i + 1];
	arr[i + 1] = arr[high];
	arr[high] = temp;
	return (i + 1);
}

void	quick_sort(char **arr, int low, int high)
{
	int	pi;

	pi = 0;
	if (low < high)
	{
		pi = partition(arr, low, high);
		if (pi > 0)
			quick_sort(arr, low, pi - 1);
		quick_sort(arr, pi + 1, high);
	}
}

char	**qsort_main(char **arr)
{
	int	len;
	char 	**duped;

	duped = ft_strdup_arr(arr);
	len = arr_size(arr);
	quick_sort(duped, 0, len - 1);
	return (duped);
}
