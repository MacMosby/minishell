/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrodenbu <mrodenbu@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 14:45:16 by mrodenbu          #+#    #+#             */
/*   Updated: 2024/09/20 14:45:18 by mrodenbu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**copy_env_unset(char **env)
{
	int		count;
	char	**env_copy;
	int		i;
	int		j;

	count = 0;
	i = 0;
	j = 0;
	while (env[count] != NULL)
		count++;
	count++;
	while (env[count] != NULL)
		count++;
	env_copy = (char **)malloc((count + 1 - 1) * sizeof(char *));
	while (i < count)
	{
		if (env[i])
			env_copy[i + j] = ft_strdup(env[i]);
		else
			j -= 1;
		i++;
	}
	env_copy[count - 1] = NULL;
	return (env_copy);
}

int	do_unset(t_state *data, char *s)
{
	int		i;
	int		j;
	char	**new_env;

	i = 0;
	while (data->env[i])
	{
		j = 0;
		while (data->env[i][j])
		{
			if (data->env[i][j] == '=')
			{
				if ((ft_strncmp(ft_substr(data->env[i], 0, j), s, j) == 0)
					&& (s[j] == 0))
				{
					free(data->env[i]);
					data->env[i] = NULL;
					new_env = copy_env_unset(data->env);
					//free_strarr(data->env);
					data->env = new_env;
					return (0);
				}
				else
					break ;
			}
			j++;
		}
		i++;
	}
	return (0);
}

int	ft_unset(t_state *data, t_node *curr)
{
	int	i;

	i = 1;
	while (curr->args[i])
	{
		do_unset(data, curr->args[i]);
		i++;
	}
	return (0);
}
