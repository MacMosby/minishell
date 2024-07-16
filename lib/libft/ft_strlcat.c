/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wel-safa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 17:46:32 by wel-safa          #+#    #+#             */
/*   Updated: 2023/05/10 14:56:31 by wel-safa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	srcl;
	size_t	dstl;

	i = 0;
	srcl = ft_strlen(src);
	dstl = ft_strlen(dst);
	if (size < dstl + 1)
		return (srcl + size);
	while (i < size - dstl - 1 && src[i])
	{
		dst[dstl + i] = src[i];
		i++;
	}
	dst[dstl + i] = 0;
	return (srcl + dstl);
}
/*
int	main(void)
{
	char dest[15];
	memset(dest, 0, 15);
	memset(dest, 'r', 6);
	dest[10] = 'a';
	printf("%zu\n", ft_strlcat(dest, "lorem ipsum dolor sit amet", 1));
	write(1, dest, 15);
}
*/
