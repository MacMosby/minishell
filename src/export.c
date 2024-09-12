/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrodenbu <mrodenbu@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 18:59:57 by mrodenbu          #+#    #+#             */
/*   Updated: 2024/09/12 18:59:59 by mrodenbu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_exp_env(t_state *state, char **env)
{
	t_list	*head;
	t_exp	*content;
	int		i;
	int		j;

	i = 0;
	while (env[i])
	{
		content = malloc(sizeof(t_exp));
		if (!content)
			// EXIT HANDLE
			exit(1);
		j = 0;
		while (env[i][j])
		{
			if (env[i][j] == '=')
			{
				content->key = ft_substr(env[i], 0, j);
				content->value = ft_substr(env[i], j + 1, ft_strlen(env[i]) - 1);
				ft_lstadd_back(&head,ft_lstnew(content));
			}
			j++;
		}
		i++;
	}
	state->exp_env = &head;
}
