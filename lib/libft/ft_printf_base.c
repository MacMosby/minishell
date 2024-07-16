/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wel-safa <wel-safa@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 15:13:07 by wel-safa          #+#    #+#             */
/*   Updated: 2024/03/03 18:30:44 by wel-safa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
size_t	ft_strlen(const char *s)
{
	size_t	n;

	n = 0;
	while (*s)
	{
		n++;
		s++;
	}
	return (n);
}
*/

int	ft_strlen_valid(char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '+' || str[i] == '-' || str[i] == ' ')
			return (-1);
		if (!(str[i] > ' ' && str[i] <= '~'))
			return (-1);
		while (str[j])
		{
			if (j != i && str[j] == str[i])
				return (-1);
			j++;
		}
		i++;
		j = 0;
	}
	return (i);
}

int	ft_putchar(char c)
{
	write(1, &c, 1);
	return (1);
}

int	ft_putnbr_case(char c, unsigned int nbr)
{
	char	*lowerbase;
	char	*upperbase;

	lowerbase = "0123456789abcdef";
	upperbase = "0123456789ABCDEF";
	if (c == 'x')
		return (ft_putnbr_base(nbr, lowerbase, 0));
	else
		return (ft_putnbr_base(nbr, upperbase, 0));
}

int	ft_putnbr_base(unsigned long long nb, char *base, int count)
{
	if (!(ft_strlen_valid(base) > 1))
		return (0);
	if (nb / ft_strlen_valid(base) == 0)
	{
		ft_putchar(base[nb % ft_strlen_valid(base)]);
		count++;
	}
	else
	{
		count = ft_putnbr_base(nb / ft_strlen_valid(base), base, count);
		count = ft_putnbr_base(nb % ft_strlen_valid(base), base, count);
	}
	return (count);
}
