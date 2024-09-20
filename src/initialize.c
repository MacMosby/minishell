/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wel-safa <wel-safa@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 22:20:30 by wel-safa          #+#    #+#             */
/*   Updated: 2024/08/21 21:31:08 by wel-safa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* initializes pipes and store them in the data struct */
void	init_pipes(t_state *data, int i)
{
	if (data->num_of_processes < 2)
		return ;
	data->pipes = (int **)malloc((data->num_of_processes - 1) * sizeof(int *));
	if (!data->pipes)
	{
		cleanup_shell_exit(data);
		exit(1);
	}
	while (i < data->num_of_processes - 1)
	{
		data->pipes[i] = (int *)malloc(2 * sizeof(int));
		if (!data->pipes[i])
		{
			cleanup_shell_exit(data);
			exit(1);
		}
		if (pipe(data->pipes[i]) == -1)
		{
			cleanup_shell_exit(data);
			exit(1);
		}
		i++;
	}
}

/* creates the data structure for the array of process IDs */
void	init_pids(t_state *data)
{
	data->pids = (int *)malloc(data->num_of_processes * sizeof(int));
	if (!data->pids)
	{
		cleanup_shell_exit(data);
		exit(1);
	}
}

void	init_builtins(t_state *state)
{
	state->builtins[0] = "echo";
	state->builtins[1] = "cd";
	state->builtins[2] = "pwd";
	state->builtins[3] = "export";
	state->builtins[4] = "unset";
	state->builtins[5] = "env";
	state->builtins[6] = "exit";
	state->builtins[7] = NULL;
}

void	init_minishell(t_state *state, char **envp)
{
	state->input = NULL;
	state->exit_status = 0;
	state->env = NULL;
	state->words = NULL;
	state->cmds = NULL;
	state->num_of_processes = 0;
	state->pipes = NULL;
	state->pids = NULL;
	init_builtins(state);
	set_env(state, envp);
}
