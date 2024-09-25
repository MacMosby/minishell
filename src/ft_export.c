/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrodenbu <mrodenbu@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 14:40:16 by mrodenbu          #+#    #+#             */
/*   Updated: 2024/09/20 14:40:21 by mrodenbu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	do_export(t_state *data, char *s)
{
	int		i;
	char	*key;
	char	*value;

	i = 0;
	if (!ft_isalpha(s[i]))
		return (1);
	i++;
	while (s[i])
	{
		if (!ft_isalnum(s[i]) && s[i] != '=' && s[i] != '_')
			return (1);
		if (s[i] == '=')
		{
			key = ft_substr(s, 0, i);
			value = ft_substr(s, i + 1, ft_strlen(s) - i);
			set_env_var(data, key, value, 1);
			free(key);
			free(value);
			return (0);
		}
		i++;
	}
	key = ft_substr(s, 0, i);
	set_env_var(data, key, NULL, 0);
	free(key);
	return (0);
}

void	print_export_line(char *s)
{
	int		i;
	char	*key;
	char	*value;

	i = 0;
	value = NULL;
	while (s[i])
	{
		if (s[i] == '=')
		{
			value = ft_substr(s, i + 1, ft_strlen(s) - i);
			break ;
		}
		i++;
	}
	key = ft_substr(s, 0, i);
	printf("declare -x %s", key);
	if (value)
	{
		printf("=\"%s\"", value);
	}
	free(key);
	free(value);
	printf("\n");
}

char	*find_min_export_line(char **env, char *min, char *last, int i)
{
	if (last)
		min = NULL;
	while (env[i])
	{
		if (!last)
		{
			if (ft_strncmp(min, env[i], ft_max_len(min, env[i])) > 0)
				min = env[i];
		}
		else
		{
			if (ft_strncmp(env[i], last, ft_max_len(env[i], last)) > 0)
			{
				if (!min)
					min = env[i];
				else
				{
					if (ft_strncmp(min, env[i], ft_max_len(min, env[i])) > 0)
						min = env[i];
				}
			}
		}
		i++;
	}
	return (min);
}

void	print_export_list(char **env)
{
	int		j;
	int		len;
	char	*last;
	char	*min;

	last = NULL;
	if (!env || !(*env))
		return ;
	min = env[0];
	j = 0;
	len = 0;
	while (env[len])
		len++;
	while (j < len)
	{
		min = find_min_export_line(env, min, last, 0);
		if (last && min)
		{
			if (!ft_strncmp(min, last, ft_max_len(min, last)))
				return ;
		}
		print_export_line(min);
		last = min;
		j++;
	}
}

// needs to work without arguments and with more than one
int	ft_export(t_state *data, t_node *curr)
{
	int	i;
	int	ret;
	int	status;

	ret = 0;
	status = 0;
	i = 1;
	if (!curr->args[i])
	{
		print_export_list(data->env);
		return (0);
	}
	while (curr->args[i])
	{
		ret = do_export(data, curr->args[i]);
		if (ret)
			status = ret;
		i++;
	}
	if (status)
		write(2, " not a valid identifier\n", 24);
	return (status);
}
