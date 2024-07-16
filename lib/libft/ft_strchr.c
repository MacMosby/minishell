/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wel-safa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 18:20:46 by wel-safa          #+#    #+#             */
/*   Updated: 2023/05/10 18:50:47 by wel-safa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (char) c)
			return ((char *)(s + i));
		i++;
	}
	if (!s[i] && !(char)c)
		return ((char *)(s + i));
	return (0);
}
/*
int	main(void)
{
	char *s1;
	char *s2;

	s1 = ft_strchr("teste", 1024);
	s2 = strchr("teste", 1024);
	if (ft_strchr("teste", 1024) == strchr("teste", 1024))
		printf("equal\n");
	else
		printf("not equal\n");
}*/
