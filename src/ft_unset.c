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

int	get_env_len(char **env)
{
	int	i;

	i = 0;
	while (env[i])
		i++;
	i++;
	while (env[i])
		i++;
	return (i);
}

char	**copy_env_unset(t_state *state, char **env)
{
	char	**env_copy;
	int		i;
	int		j;
	int		count;

	i = 0;
	j = 0;
	count = get_env_len(env);
	env_copy = (char **)malloc((count + 1 - 1) * sizeof(char *));
	if (!env_copy)
		error_exit(state);
	while (i < count)
	{
		if (env[i])
		{
			env_copy[i + j] = ft_strdup(env[i]);
			free(env[i]);
		}
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
	new_env = copy_env_unset(data, data->env);
	free(data->env);
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
