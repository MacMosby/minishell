/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wel-safa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 12:01:01 by wel-safa          #+#    #+#             */
/*   Updated: 2023/05/10 13:25:04 by wel-safa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isprint(int c)
{
	return (c >= 32 && c < 127);
}
/*
#include <stdio.h>
#include <ctype.h>

int	main(void)
{
	printf("c = 128: %i\n", ft_isprint(128));
	printf("c = 128: %i\n\n", isprint(128));
	printf("c = 31: %i\n", ft_isprint(31));
	printf("c = 31: %i\n\n", isprint(31));
	printf("c = 32: %i\n", ft_isprint(32));
	printf("c = 32: %i\n\n", isprint(32));
}
*/
