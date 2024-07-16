/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wel-safa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 16:18:23 by wel-safa          #+#    #+#             */
/*   Updated: 2023/05/12 17:10:48 by wel-safa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if ((char)*((char *)s) == (char)c)
			return ((void *)s);
		s++;
		i++;
	}
	return (0);
}
/*
int	main(void)
{
	//char *str = "Bonjourno";
	const char *res;
	res = ft_memchr("Bonjour", 'o', 7);
	if (!res)
		printf("NULL\n");
	else
		printf("%s\n", res);
}*/
