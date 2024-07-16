/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wel-safa <wel-safa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 12:45:28 by wel-safa          #+#    #+#             */
/*   Updated: 2023/05/14 13:42:50 by wel-safa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t	bytes;
	void	*ptr;

	bytes = size * nmemb;
	if (size != 0 && nmemb != 0 && bytes / size != nmemb)
		return (NULL);
	ptr = malloc (bytes);
	if (ptr == 0)
		return (0);
	ft_bzero(ptr, bytes);
	return (ptr);
}
