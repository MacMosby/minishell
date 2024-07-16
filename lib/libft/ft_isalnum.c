/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wel-safa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 15:12:01 by wel-safa          #+#    #+#             */
/*   Updated: 2023/05/02 15:21:07 by wel-safa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalnum(int c)
{
	if (c >= '0' && c <= '9')
		return (8);
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (8);
	return (0);
}
/*
#include <ctype.h>
#include <stdio.h>

int	main(int argc, char *argv[])
{
	if (argc == 2)
	{
		printf("ft_isalnum('%c'): %i\n", argv[1][0], ft_isalnum(argv[1][0]));
		printf("isalnum('%c'): %i\n", argv[1][0], isalnum(argv[1][0]));
	}
	return (0);
}
*/
