/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wel-safa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 15:58:46 by wel-safa          #+#    #+#             */
/*   Updated: 2023/05/10 17:06:17 by wel-safa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;

	i = 0;
	if (!dest && !src)
		return (0);
	while (i < n)
	{
		((char *)dest)[i] = ((char *)src)[i];
		i++;
	}
	return (dest);
}
/*
int	main(void)
{
	//char s1[100] = "Koala bears are cute!";
	//char s2[100] = "Down with the patrearchy!";
	//printf("%p\n", memcpy(((void *)0), ((void *)0), 3));
	//printf("%s\n", s1);
	printf("%p\n", ft_memcpy(((void *)0), ((void *)0), 3));
	return (0);
}*/
