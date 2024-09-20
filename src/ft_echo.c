/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrodenbu <mrodenbu@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 14:32:19 by mrodenbu          #+#    #+#             */
/*   Updated: 2024/09/20 14:32:20 by mrodenbu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* checks if the input string is the -n flag for echo to not print \n */
int	flag_check(char *str, int *flag)
{
	int	i;

	if (!str)
		return (0);
	if (str[0] == '-')
	{
		i = 1;
		while (str[i])
		{
			if (str[i] != 'n')
				return (0);
			i++;
		}
		if (i > 1)
		{
			*flag = 1;
			return (1);
		}
	}
	return (0);
}

/* takes an array of strings an and prints them without the first one */
int	ft_echo(char **arr)
{
	int	i;
	int	flag;
	int	first;

	i = 1;
	flag = 0;
	first = 1;
	while (arr[i] && flag_check(arr[i], &flag))
	{
		i++;
	}
	while (arr[i])
	{
		if (first)
		{
			printf("%s", arr[i]);
			first = 0;
		}
		else
			printf(" %s", arr[i]);
		i++;
	}
	if (!flag)
		printf("%s\n", "");
	return (0);
}
