/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wel-safa <wel-safa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 18:16:26 by wel-safa          #+#    #+#             */
/*   Updated: 2024/08/03 13:48:13 by wel-safa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_env(t_state *state, char **envp)
{
	state->env = copy_env(envp, 0);

	/*********************TO DO**********************/
	// check essential environment variables
	// if they do not exit, create essential ones
	// essential ones: PATH, HOME, SHELL, USER ???
	/************************************************/
}

/*Returns a exact malloced copy of env if add_flag is false.
if add_flag is true, it returns a malloced copy of env
with an extra NULL pointer at the end so with two NULL pointers
instead of just one.
*/
char	**copy_env(char **env, int add_flag)
{
	int		count;
	char	**env_copy;
	int		i;
	int		add;	// heredoc

	add = 0;
	if (add_flag)
		add = 1;
	count = 0;
	i = 0;
	while (env[count] != NULL)
		count++;
	env_copy = (char **)malloc((count + 1 + add) * sizeof(char *));
	while (i < count)
	{
		env_copy[i] = ft_strdup(env[i]);
		i++;
	}
	env_copy[count] = NULL;
	if (add_flag)
		env_copy[count + 1] = NULL;
	return (env_copy);
}

/*searches environment variables, returns pointer to value of var in env if it finds it
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

/*searches for var in env and sets it to value
if it does not find the variable, it creates it
if the value pointer is NULL, it does not set a value or removes set value*/
void	set_env_var(t_state *state, char *var, char *value, int equal)
{
	int		i;
	size_t	len;
	char	**newenv;

	len = ft_strlen(var);
	i = 0;
	newenv = NULL;
	while (state->env[i])
	{
		if ((ft_strncmp(state->env[i], var, len) == 0)
			&& (state->env[i][len] == '=' || state->env[i][len] == 0))
		{
			// found variable
			// modify variable with value or remove value
			free(state->env[i]);
			// MARC START
			if (equal)
				state->env[i] = create_new_var(var, value);
			else
				state->env[i] = ft_strdup(var);
			// MARC END
			return ;
		}
		i++;
	}
	// Need to create a variable in the env variable.
	// so we have to re-allocate the environment with an extra string "var=value" or "var="
	newenv = copy_env(state->env, 1);
	i = 0;
	while (newenv[i])
		i++;
	// MARC START
	if (equal)
		newenv[i] = create_new_var(var, value);
	else
		newenv[i] = ft_strdup(var);
	// MARC END
	free_strarr(state->env);
	state->env = newenv;
}

/*Takes strings var and value and returns a malloced string "var=value"
if value is NULL, it returns "var="*/
char	*create_new_var(char *var, char *value)
{
	char	*env_var;
	size_t	var_len;
	size_t	value_len;

	if (!var)
		return (NULL); // input error
	var_len = ft_strlen(var);
	value_len = 0;
	if (value)
		value_len = ft_strlen(value);
	env_var = (char *)malloc(sizeof(char) * (var_len + value_len + 2));
	if (env_var == NULL)
		// protect malloc
		exit(1);
	ft_memcpy(env_var, var, var_len);
	ft_memcpy(env_var + var_len, "=", 1);
	if (value)
		ft_memcpy(env_var + var_len + 1, value, value_len);
	env_var[var_len + value_len + 1] = 0;
	return (env_var);
}
