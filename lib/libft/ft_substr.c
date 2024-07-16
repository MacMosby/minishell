/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wel-safa <wel-safa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 15:08:10 by wel-safa          #+#    #+#             */
/*   Updated: 2023/05/17 22:39:13 by wel-safa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_minsize(size_t s1, size_t s2)
{
	if (s1 < s2)
		return (s1);
	return (s2);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*subs;
	unsigned int	i;
	size_t			lcpy;

	lcpy = ft_strlen(s) - start;
	if (start >= ft_strlen(s) || len == 0)
	{
		subs = (char *)malloc(1);
		if (subs)
			subs[0] = '\0';
		return (subs);
	}
	else
		subs = (char *)malloc(ft_minsize(lcpy, len) + 1);
	if (subs == 0)
		return (0);
	i = 0;
	while (i < ft_minsize(lcpy, len))
	{
		subs[i] = s[start + i];
		i++;
	}
	subs[i] = 0;
	return (subs);
}
