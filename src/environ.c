/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wel-safa <wel-safa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 18:16:26 by wel-safa          #+#    #+#             */
/*   Updated: 2024/09/22 23:36:29 by wel-safa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_shlvl(char **shlvl_env)
{
	int		shlvl_int;
	char	*shlvl;

	shlvl_int = ft_atoi(*shlvl_env + 6) + 1;
	shlvl = ft_itoa(shlvl_int);
	*shlvl_env = strreplace(shlvl_env, shlvl, 6, ft_strlen(*shlvl_env));
	free(shlvl);
}

/*Returns a exact malloced copy of env if add_flag is false.
if add_flag is true, it returns a malloced copy of env
with an extra NULL pointer at the end so with two NULL pointers
instead of just one.
*/
char	**copy_env(t_state *state, char **env, int add_flag)
{
	int		count;
	char	**env_copy;
	int		i;

	count = 0;
	i = 0;
	while (env[count] != NULL)
		count++;
	env_copy = (char **)malloc((count + 1 + add_flag) * sizeof(char *));
	if (!env_copy)
		error_exit(state);
	while (i < count)
	{
		env_copy[i] = ft_strdup(env[i]);
		if (ft_strncmp(env_copy[i], "SHLVL=", 6) == 0)
			update_shlvl(&(env_copy[i]));
		i++;
	}
	env_copy[count] = NULL;
	if (add_flag)
		env_copy[count + 1] = NULL;
	return (env_copy);
}
