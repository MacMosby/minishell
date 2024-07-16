/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wel-safa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 17:09:16 by wel-safa          #+#    #+#             */
/*   Updated: 2023/05/10 13:34:00 by wel-safa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	srcl;
	size_t	i;

	i = 0;
	srcl = ft_strlen(src);
	if (size == 0)
		return (srcl);
	while ((i < (size - 1)) && (src[i]))
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = 0;
	return (srcl);
}
/*
int	main(void)
{
	//char *s1 = "Koalas are cute!";
	//char s2[19];
	char dest[15];
	printf("%zu\n", ft_strlcpy(dest, "lorem ipsum dolor sit amet", 0));
	write(1, dest, 15);
}*/
