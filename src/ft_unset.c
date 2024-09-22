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

char	**copy_env_unset(t_state *state, char **env, int count)
{
	char	**env_copy;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (env[count] != NULL)
		count++;
	count++;
	while (env[count] != NULL)
		count++;
	env_copy = (char **)malloc((count + 1 - 1) * sizeof(char *));
	if (!env_copy)
		error_exit(state);
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

void	do_unset(t_state *data, int i)
{
	char	**new_env;

	free(data->env[i]);
	data->env[i] = NULL;
	new_env = copy_env_unset(data, data->env, 0);
	free_strarr(data->env);
	data->env = new_env;
}

int	find_unset_var(t_state *data, char *s)
{
	int		i;
	int		len;

	i = 0;
	len = ft_strlen(s);
	while (data->env[i])
	{
		if (ft_strncmp(s, data->env[i], len) == 0
			&& (data->env[i][len] == '=' || data->env[i][len] == 0))
		{
			do_unset(data, i);
			return (0);
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
		find_unset_var(data, curr->args[i]);
		i++;
	}
	return (0);
}
