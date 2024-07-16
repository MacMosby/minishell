/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wel-safa <wel-safa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 13:45:13 by wel-safa          #+#    #+#             */
/*   Updated: 2024/07/14 16:58:59 by wel-safa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
it duplicates string s and returns a malloced copy*/
char	*ft_strdup(const char *s)
{
	size_t	size;
	char	*ptr;

	size = ft_strlen(s);
	ptr = (char *)malloc(size + 1);
	if (!ptr)
		return (0);
	return (ft_memcpy(ptr, s, size + 1));
}
