/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wel-safa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 19:07:14 by wel-safa          #+#    #+#             */
/*   Updated: 2023/05/10 18:56:39 by wel-safa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	sl;

	sl = ft_strlen(s);
	if ((char)c == 0)
		return ((char *)(&s[sl]));
	while (sl > 0)
	{
		if (s[sl - 1] == (char)c)
		{
			return ((char *)(&s[sl - 1]));
		}
		sl--;
	}
	return (0);
}
/*
int	main(void)
{
	
	char	*str;
	char	str2[] = "bonjour";
	str = ft_strrchr(str2, 's');
	if (!str)
		printf("NULL");
	else
		printf("%s\n", str);
		
		
	char *s1 = "Koalas are cute!";
	printf("test1:\n");
	printf("%s\n", ft_strrchr(s1, ' '));
	printf("%s\n", strrchr(s1, ' '));
	printf("test2:\n");
	printf("%s\n", ft_strrchr(s1, 0));
	printf("%s\n", strrchr(s1, 0));
	char *s2 = "";
	printf("test3:\n");
	printf("%s\n", ft_strrchr(s2, 0));
	printf("%s\n", strrchr(s2, 0));
	printf("test4:\n");
	printf("%s\n", ft_strrchr(s2, ' '));
	printf("%s\n", strrchr(s2, ' '));
	printf("test5:\n");
	printf("%s\n", ft_strrchr("b", 'a'));
	printf("%s\n", strrchr("b", 'a'));
}
*/
