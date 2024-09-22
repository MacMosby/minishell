/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wel-safa <wel-safa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 17:25:02 by mrodenbu          #+#    #+#             */
/*   Updated: 2024/09/22 15:31:18 by wel-safa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	do_cmd_execution(t_state *state, t_node *curr)
{
	int	exit_status;

	if (curr->cmd_flag == PATH)
	{
		if (execve(curr->cmd, curr->args, state->env) == -1)
		{
			cleanup_shell_exit(state);
			exit(3);
		}
	}
	else if (curr->cmd_flag == BUILTIN)
	{
		exit_status = invoke_builtin(state, curr);
		cleanup_shell_exit(state);
		exit(exit_status);
	}
}

/* creates a child process and executes the command */
void	fork_executor(t_state *data, t_node *curr, int i)
{
	int	exit_status;

	data->pids[i] = fork();
	if (data->pids[i] == -1)
		error_exit(data);
	if (data->pids[i] == 0)
	{
		redirect_in_out(data, curr, i);
		close_pipes(data);
		if (curr->err_flag == CMD_OK && curr->cmd)
			do_cmd_execution(data, curr);
		else
		{
			exit_status = curr->err_flag;
			cleanup_shell_exit(data);
			exit(exit_status);
		}
	}
}

/* iterates over list of commands and executes them one by one */
void	execution_loop(t_state *data)
{
	t_list	*curr;
	int		i;

	i = 0;
	curr = data->cmds;
	while (i < data->num_of_processes)
	{
		fork_executor(data, curr->content, i);
		curr = curr->next;
		i++;
	}
	close_pipes(data);
}

void	execute_single_builtin(t_state *state, t_node *cmd)
{
	int	fd_std_in;
	int	fd_std_out;

	fd_std_in = dup(STDIN_FILENO);
	fd_std_out = dup(STDOUT_FILENO);
	redirect_in_out(state, cmd, 0);
	if (cmd->err_flag == CMD_OK && cmd->cmd)
		state->exit_status = invoke_builtin(state, cmd);
	dup2(fd_std_in, STDIN_FILENO);
	close(fd_std_in);
	dup2(fd_std_out, STDOUT_FILENO);
	close(fd_std_out);
}

/* iterate over the linked list and executes the commands one by one */
void	executor(t_state *data)
{
	t_node	*cmd;

	if (!data->cmds)
		return ;
	cmd = (t_node *)data->cmds->content;
	init_pipes(data, 0);
	init_pids(data);
	if (data->num_of_processes == 1 && cmd->cmd_flag == BUILTIN)
		execute_single_builtin(data, cmd);
	else
	{
		execution_loop(data);
		wait_loop(data);
	}
}
