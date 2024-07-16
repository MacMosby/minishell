/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wel-safa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 14:28:12 by wel-safa          #+#    #+#             */
/*   Updated: 2023/05/02 14:59:52 by wel-safa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (2048);
	return (0);
}
/*
#include <ctype.h>
#include <stdio.h>

int	main(int argc, char **argv)
{
	if (argc == 2)
	{
		printf("ft_isdigit('%c'): %i\n", argv[1][0], ft_isdigit(argv[1][0]));
		printf("isdigit('%c'): %i\n\n", argv[1][0], isdigit(argv[1][0]));
	}

	printf("ft_isdigit('9'): %i\n", ft_isdigit('9'));
	printf("isdigit('9'): %i\n\n", isdigit('9'));

	printf("ft_isdigit(0): %i\n", ft_isdigit(0));
	printf("isdigit(0): %i\n\n", ft_isdigit(0));

	printf("ft_isdigit(48): %i\n", ft_isdigit(48));
	printf("isdigit(48): %i\n\n", isdigit(48));

	return (0);
}*/
