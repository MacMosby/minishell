/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wel-safa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 17:45:39 by wel-safa          #+#    #+#             */
/*   Updated: 2023/05/12 18:03:11 by wel-safa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	bi;
	size_t	si;

	if (ft_strlen(little) == 0)
		return ((char *)big);
	bi = 0;
	si = 0;
	while (bi < len && big[bi])
	{
		si = 0;
		if (big[bi] == little[si])
		{
			while (big[bi + si] == little[si] && little[si] && bi + si < len)
				si++;
			if (!little[si])
				return ((char *)&big[bi]);
		}
		bi++;
	}
	return (0);
}
