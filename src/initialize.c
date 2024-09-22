/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wel-safa <wel-safa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 22:20:30 by wel-safa          #+#    #+#             */
/*   Updated: 2024/09/22 23:03:05 by wel-safa         ###   ########.fr       */
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
		error_exit(data);
	while (i < data->num_of_processes - 1)
	{
		data->pipes[i] = (int *)malloc(2 * sizeof(int));
		if (!data->pipes[i])
			error_exit(data);
		if (pipe(data->pipes[i]) == -1)
			error_exit(data);
		i++;
	}
}

/* creates the data structure for the array of process IDs */
void	init_pids(t_state *data)
{
	data->pids = (int *)malloc(data->num_of_processes * sizeof(int));
	if (!data->pids)
		error_exit(data);
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

void	init_minishell(t_state *state, int argc, char **argv, char **envp)
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
	state->env = copy_env(state, envp, 0);
	argc = ft_strlen(argv[0]);
}
