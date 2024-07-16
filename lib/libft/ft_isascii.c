/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wel-safa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 11:49:20 by wel-safa          #+#    #+#             */
/*   Updated: 2023/05/03 12:00:40 by wel-safa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isascii(int c)
{
	return (c >= 0 && c <= 127);
}
/*
#include <stdio.h>
#include <ctype.h>

int	main(void)
{
	printf("ft_isascii(129)= %i\n", ft_isascii(129));
	printf("isascii(129)= %i\n", isascii(129));
	return (0);
}
*/
