/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wel-safa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 12:49:27 by wel-safa          #+#    #+#             */
/*   Updated: 2023/05/03 14:10:53 by wel-safa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		((char *)s)[i] = c;
		i++;
	}
	return (s);
}
/*
int	main(void)
{
	char str[100] = "ahdlahfls";
	char str2[100] = "ahdlahfls";
	void *p;

	p = str;
	printf("%p\n", ft_memset(p, 'a', 4));
	printf("%s\n\n", str);
	p = str2;
	printf("%p\n", memset(p, '0', 4));
	printf("%s\n\n", str2);

	int arr[5] = {1, 2, 3, 4, 5};
	int arr1[5] = {1, 2, 3, 4, 5};
	void *q;
	q = arr;
	printf("%p\n", ft_memset(arr, 35, 5));
	printf("%p\n\n", memset(arr, 35, 5));

	q = arr1;
	memset(arr1, 35, 5);
	for (int i = 0; i < 5; i++)
	{
		printf("%i ", arr[i]);
	}
	printf("\n");
	for (int i = 0; i < 5; i++)
	{
		printf("%i ", arr1[i]);
	}
}
*/
