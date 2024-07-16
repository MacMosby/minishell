/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wel-safa <wel-safa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 17:43:33 by wel-safa          #+#    #+#             */
/*   Updated: 2023/05/14 17:57:52 by wel-safa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*cstr;
	size_t	cstrl;
	size_t	i;

	cstrl = ft_strlen(s1) + ft_strlen(s2);
	if (cstrl - ft_strlen(s1) != ft_strlen(s2))
		return (0);
	cstr = (char *)malloc(cstrl + 1);
	if (cstr == NULL)
		return (NULL);
	i = 0;
	while (*s1)
	{
		cstr[i] = *s1;
		s1++;
		i++;
	}
	while (*s2)
	{
		cstr[i] = *s2;
		s2++;
		i++;
	}
	cstr[i] = 0;
	return (cstr);
}
