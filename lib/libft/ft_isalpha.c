/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wel-safa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 13:39:49 by wel-safa          #+#    #+#             */
/*   Updated: 2023/05/02 15:09:49 by wel-safa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalpha(int c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
		return (1024);
	return (0);
}

/*
#include <stdio.h>
#include <ctype.h>

int	main(int argc, char **argv)
{
	if (argc == 2)
	{
		printf("ft_isalpha('%c'): %i\n", argv[1][0], ft_isalpha(argv[1][0]));
		printf("isalpha('%c'): %i\n\n", argv[1][0], isalpha(argv[1][0]));
	}
	return (0);
}
*/
