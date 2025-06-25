/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlee <zlee@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 17:38:12 by zlee              #+#    #+#             */
/*   Updated: 2024/11/08 18:23:56 by zlee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_digit(int n)
{
	int	count;

	count = 1;
	if (n < 0)
	{
		n = -n;
		count++;
	}
	while (n > 9)
	{
		n = n / 10;
		count++;
	}
	return (count);
}

static void	assign_var(int size, char *str, int neg, int n)
{
	while (size >= neg)
	{
		str[size--] = (n % 10) + 48;
		n = n / 10;
	}
}

char	*ft_itoa(int n)
{
	int		size;
	char	*string;
	int		neg;

	neg = 0;
	size = count_digit(n);
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	if (n < 0)
	{
		neg = 1;
		n = -n;
	}
	string = (char *)malloc((size + 1) * sizeof(char));
	if (!string)
		return (0);
	string[size--] = '\0';
	if (neg == 1)
		string[0] = '-';
	assign_var(size, string, neg, n);
	return (string);
}
//
//#include <stdio.h>
//int	main(void)
//{
	//int test = -23;
	//char *test2 = ft_itoa(-234);
	//char *test3 = ft_itoa(342);
	//char *test4 = ft_itoa(800980);
	//char *ts = ft_itoa(test);
	//printf("%s\n", ts);
	//printf("%s\n", test2);
	//printf("%s\n", test3);
	//printf("%s\n", test4);
	//free(ts);
	//free(test2);
	//free(test3);
	//free(test4);
//}
