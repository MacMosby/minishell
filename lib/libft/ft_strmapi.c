/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wel-safa <wel-safa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 15:02:55 by wel-safa          #+#    #+#             */
/*   Updated: 2023/05/15 15:20:13 by wel-safa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	ssize;
	char	*res;
	size_t	i;

	i = 0;
	ssize = ft_strlen(s);
	res = (char *)malloc(ssize + 1);
	if (res == 0)
	{
		free(res);
		return (NULL);
	}
	res[ssize] = 0;
	while (i < ssize)
	{
		res[i] = f(i, s[i]);
		i++;
	}
	return (res);
}
/*
char	testfunc(unsigned int i, char c)
{
	c = c + 32;
	i = 0;
	return (c);
}

int	main(void)
{
	char *s = ft_strmapi("", testfunc);
	printf("%s\n", s);
}
*/