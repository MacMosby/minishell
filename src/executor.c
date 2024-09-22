/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wel-safa <wel-safa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 17:25:02 by mrodenbu          #+#    #+#             */
/*   Updated: 2024/09/14 21:38:59 by wel-safa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* creates a child process and executes the command */
void	fork_executor(t_state *data, t_node *curr, int i)
{
	data->pids[i] = fork();
	if (data->pids[i] == -1)
		error_exit(data);
	if (data->pids[i] == 0)
	{
		redirect_in_out(data, curr, i);
		close_pipes(data);
		if (curr->err_flag == CMD_OK && curr->cmd)
		{
			if (curr->cmd_flag == PATH)
			{
				if (execve(curr->cmd, curr->args, data->env) == -1)
					// EXIT HANDLE - do we need to clean the child process ?
					exit(3);
			}
			else if (curr->cmd_flag == BUILTIN)
				exit(invoke_builtin(data, curr));
		}
		else
			exit(curr->err_flag);
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

/* iterates over PIDs to wait for all the child processes to finish */
void	wait_loop(t_state *data)
{
	int	i;
	int	wstatus;

	i = 0;
	while (i < data->num_of_processes)
	{
		if (waitpid(data->pids[i], &wstatus, 0) == -1)
		{
			// ???
			printf("We should never get here!!!\n");
			/* if (g_signal)
				data->exit_status = 128 + g_signal; */
		}
		else
		{
			if (WIFEXITED(wstatus))
				data->exit_status = WEXITSTATUS(wstatus);
			else
				data->exit_status = 128 + g_signal;
		}
		i++;
	}
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
