/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wel-safa <wel-safa@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 22:20:30 by wel-safa          #+#    #+#             */
/*   Updated: 2024/07/19 22:09:51 by wel-safa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	state->seperators = " <>|";
	set_env(state, envp);
}
