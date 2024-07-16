/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wel-safa <wel-safa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 19:26:50 by wel-safa          #+#    #+#             */
/*   Updated: 2023/05/17 16:24:15 by wel-safa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_findchr(char const c, char const *set)
{
	while (*set)
	{
		if (*set == c)
			return (1);
		set++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;
	char	*trimstr;
	size_t	i;

	i = 0;
	start = 0;
	end = ft_strlen(s1);
	while (s1[start] && ft_findchr(s1[start], set))
		start++;
	while (end > start && ft_findchr(s1[end - 1], set))
		end--;
	trimstr = (char *)malloc(end - start + 1);
	if (trimstr == 0)
		return (0);
	while (start < end)
		trimstr[i++] = s1[start++];
	trimstr[i] = 0;
	return (trimstr);
}
