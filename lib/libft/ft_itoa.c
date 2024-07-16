/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wel-safa <wel-safa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 11:48:56 by wel-safa          #+#    #+#             */
/*   Updated: 2023/05/15 14:58:53 by wel-safa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_nsize(long int ln)
{
	size_t	nsize;

	nsize = 0;
	if (ln == 0)
		return (1);
	if (ln < 0)
	{
		nsize++;
		ln *= -1;
	}
	while (ln > 0)
	{
		ln /= 10;
		nsize++;
	}
	return (nsize);
}

void	ft_populate(long int ln, char *nstr, size_t i)
{
	if (ln == 0)
		nstr[0] = '0';
	while (ln > 0)
	{
		nstr[i] = (ln % 10) + '0';
		ln /= 10;
		i--;
	}
}

char	*ft_itoa(int n)
{
	long int	ln;
	size_t		nsize;
	char		*nstr;

	ln = n;
	nsize = ft_nsize(ln);
	nstr = (char *)malloc((nsize + 1) * sizeof(char));
	if (nstr == 0)
	{
		free(nstr);
		return (NULL);
	}
	if (ln < 0)
	{
		nstr[0] = '-';
		ln *= -1;
	}
	nstr[nsize] = 0;
	ft_populate(ln, nstr, nsize - 1);
	return (nstr);
}
/*
int	main(void)
{
	char *res = ft_itoa(9);
	printf("%s\n", res);
}
*/