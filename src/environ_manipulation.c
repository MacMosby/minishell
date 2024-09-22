/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ_manipulation.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wel-safa <wel-safa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 23:33:11 by wel-safa          #+#    #+#             */
/*   Updated: 2024/09/22 23:38:26 by wel-safa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*searches environment variables, returns pointer to 
value of var in env if it finds it
it will return NULL if var has no value or not found*/
char	*find_var_value(t_state *state, char *var)
{
	int		i;
	size_t	len;

	if (!var)
		return (NULL);
	len = ft_strlen(var);
	i = 0;
	while (state->env[i])
	{
		if ((ft_strncmp(state->env[i], var, len) == 0)
			&& (state->env[i][len] == '='))
		{
			if (state->env[i][len + 1] != 0)
				return (state->env[i] + len + 1);
			else
				return (NULL);
		}
		i++;
	}
	return (NULL);
}

/*Takes strings var and value and returns a malloced string "var=value"
if value is NULL, it returns "var="*/
char	*create_new_var(t_state *state, char *var, char *value)
{
	char	*env_var;
	size_t	var_len;
	size_t	value_len;

	if (!var)
		return (NULL);
	var_len = ft_strlen(var);
	value_len = 0;
	if (value)
		value_len = ft_strlen(value);
	env_var = (char *)malloc(sizeof(char) * (var_len + value_len + 2));
	if (!env_var)
		error_exit(state);
	ft_memcpy(env_var, var, var_len);
	ft_memcpy(env_var + var_len, "=", 1);
	if (value)
		ft_memcpy(env_var + var_len + 1, value, value_len);
	env_var[var_len + value_len + 1] = 0;
	return (env_var);
}

/*creates new environment to accomodate exporting new variable*/
void	create_new_env(t_state *state, char *var, char *value, int equal)
{
	int		i;
	char	**newenv;

	i = 0;
	newenv = copy_env(state, state->env, 1);
	while (newenv[i])
		i++;
	if (equal)
		newenv[i] = create_new_var(state, var, value);
	else
		newenv[i] = ft_strdup(var);
	free_strarr(state->env);
	state->env = newenv;
}

/*searches for var in env and sets it to value
if it does not find the variable, it creates it
if the value pointer is NULL, it does not set a value or removes set value*/
void	set_env_var(t_state *state, char *var, char *value, int equal)
{
	int		i;
	size_t	len;

	len = ft_strlen(var);
	i = 0;
	while (state->env[i])
	{
		if ((ft_strncmp(state->env[i], var, len) == 0)
			&& (state->env[i][len] == '=' || state->env[i][len] == 0))
		{
			free(state->env[i]);
			if (equal)
				state->env[i] = create_new_var(state, var, value);
			else
				state->env[i] = ft_strdup(var);
			return ;
		}
		i++;
	}
	create_new_env(state, var, value, equal);
}
