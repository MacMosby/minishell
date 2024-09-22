/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrodenbu <mrodenbu@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 21:03:16 by mrodenbu          #+#    #+#             */
/*   Updated: 2024/09/20 21:03:18 by mrodenbu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* takes two strings s1 and s2 as inputs, joins them and returns the result
after freeing s1 and s2 */
char	*ft_join_free(t_state *state, char *s1, char *s2, size_t i)
{
	char	*str;
	size_t	len;
	size_t	j;

	if (!s1)
		s1 = ft_strdup("");
	len = ft_strlen(s1) + ft_strlen(s2);
	str = (char *)ft_calloc((len + 1), sizeof(char));
	if (!str)
		error_exit(state);
	while (i < ft_strlen(s1))
	{
		str[i] = s1[i];
		i++;
	}
	j = 0;
	while (j < ft_strlen(s2))
	{
		str[i + j] = s2[j];
		j++;
	}
	free(s1);
	free(s2);
	return (str);
}
