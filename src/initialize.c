/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wel-safa <wel-safa@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 22:20:30 by wel-safa          #+#    #+#             */
/*   Updated: 2024/08/21 14:33:26 by wel-safa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_builtins(t_state *state)
{
	state->builtins[0] = ft_strdup("echo");
	state->builtins[1] = ft_strdup("cd");
	state->builtins[2] = ft_strdup("pwd");
	state->builtins[3] = ft_strdup("export");
	state->builtins[4] = ft_strdup("unset");
	state->builtins[5] = ft_strdup("env");
	state->builtins[6] = ft_strdup("exit");
	// check if any of the builtins is NULL i.e. malloc error
}

void	init_minishell(t_state *state, char **envp)
{
	state->input = NULL;
	state->last_exit_status = 0;
	state->env = NULL;
	state->words = NULL;
	state->cmds = NULL;
	state->num_of_processes = 0;
	state->pipes = NULL;
	state->pids = NULL;
	state->builtins = (char **) malloc (8 * sizeof(char *));
	state->builtins[7] = NULL;
	init_builtins(state);
	set_env(state, envp);
}
