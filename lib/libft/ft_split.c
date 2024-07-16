/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wel-safa <wel-safa@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 19:41:53 by wel-safa          #+#    #+#             */
/*   Updated: 2024/03/03 19:28:11 by wel-safa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Checks if s is NULL or empty string checked in ft_arrsize */
/* Returns size of array of strings */
size_t	ft_arrsize(char const *s, char c)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	if (ft_strlen(s) == 0 || s[0] == 0)
		return (0);
	if (s[0] != c)
	{
		count++;
		i++;
	}
	while (s[i])
	{
		if (s[i] == c && s[i + 1] != 0 && s[i + 1] != c)
			count++;
		i++;
	}
	return (count);
}

size_t	ft_splitmalloc(size_t arrsize, char const *s, char **splits, char c)
{
	size_t	arri;
	size_t	i;
	size_t	j;
	size_t	si;

	i = 0;
	j = 0;
	arri = 0;
	while (arri < arrsize)
	{
		while (s[i] == c && s[i])
			i++;
		j = i;
		while (s[j] != c && s[j])
			j++;
		splits[arri] = (char *)malloc((j - i + 1) * sizeof(char));
		if (splits[arri] == 0)
			return (arri);
		si = 0;
		while (i < j)
			splits[arri][si++] = s[i++];
		splits[arri][si] = 0;
		arri++;
	}
	return (arri);
}

void	ft_freesplits(size_t arri, char **splits)
{
	size_t	i;

	i = 0;
	while (i <= arri)
		free(splits[i++]);
	free(splits);
}

char	**ft_split(char const *s, char c)
{
	size_t	arrsize;
	char	**splits;
	size_t	arri;

	arrsize = ft_arrsize(s, c);
	splits = (char **)malloc((arrsize + 1) * sizeof(char *));
	if (splits == 0)
	{
		free(splits);
		return (NULL);
	}
	splits[arrsize] = NULL;
	if (arrsize > 0)
	{
		arri = ft_splitmalloc(arrsize, s, splits, c);
		if (arri != arrsize)
		{
			ft_freesplits(arri, splits);
			return (NULL);
		}
	}
	return (splits);
}
/*
#include <malloc.h>
int	main(void)
{
	char **tab = ft_split("  tripouille  42  ", ' ');
	void *p = malloc (ft_strlen("tripouille") + 1);

	printf("%zu\n", malloc_usable_size(p));
	printf("%zu\n", malloc_usable_size(tab[0]));
	printf("%s\n", tab[0]);
	printf("%s\n", tab[1]);
	printf("%s\n", tab[2]);
}
*/