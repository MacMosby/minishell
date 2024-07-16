/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wel-safa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 15:45:35 by wel-safa          #+#    #+#             */
/*   Updated: 2023/05/08 15:58:35 by wel-safa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		((char *)s)[i] = 0;
		i++;
	}
}
/*
int	main(void)
{
	int i = 0;
	char s[100] = "skghogwiegolwiglog";
	bzero((void *)s, 10);
	while (i < 50)
	{
		write(1, &(s[i]), 1);
		i++;
	}
}*/
