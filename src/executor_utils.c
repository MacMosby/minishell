/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wel-safa <wel-safa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 15:45:10 by mrodenbu          #+#    #+#             */
/*   Updated: 2024/09/22 16:51:45 by wel-safa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_fds(t_state *state)
{
	t_list	*curr;
	t_node	*cmd;

	curr = state->cmds;
	while (curr)
	{
		cmd = (t_node *) curr->content;
		if (cmd->fd_in != 0)
			close(cmd->fd_in);
		if (cmd->fd_out != 1)
			close(cmd->fd_out);
		curr = curr->next;
	}
}

void	redirect_output(t_node *curr)
{
	if (curr->fd_out != STDOUT_FILENO)
	{
		dup2(curr->fd_out, STDOUT_FILENO);
		close(curr->fd_out);
	}
}

/* redirects the input and output of the cmd to pipes and/or files */
void	redirect_in_out(t_state *data, t_node *curr, int i)
{
	int	fd[2];

	redirect_to_pipes(data, i);
	if (curr->fd_in != STDIN_FILENO)
	{
		if (curr->fd_in == -1)
		{
			if (pipe(fd) == -1)
				error_exit(data);
			write(fd[WRITE_END], curr->hd_content, ft_strlen(curr->hd_content));
			dup2(fd[READ_END], STDIN_FILENO);
			close(fd[WRITE_END]);
			close(fd[READ_END]);
		}
		else
		{
			dup2(curr->fd_in, STDIN_FILENO);
			close(curr->fd_in);
		}
	}
	redirect_output(curr);
}

/* creates the redirections to pipes before looking for infiles/outfiles */
void	redirect_to_pipes(t_state *data, int i)
{
	if (i > 0)
	{
		dup2(data->pipes[i - 1][READ_END], STDIN_FILENO);
	}
	if (i < data->num_of_processes - 1)
	{
		dup2(data->pipes[i][WRITE_END], STDOUT_FILENO);
	}
}

/* iterates over PIDs to wait for all the child processes to finish */
void	wait_loop(t_state *data)
{
	int	i;
	int	wstatus;

	i = 0;
	while (i < data->num_of_processes)
	{
		waitpid(data->pids[i], &wstatus, 0);
		if (WIFEXITED(wstatus))
			data->exit_status = WEXITSTATUS(wstatus);
		else
			data->exit_status = 128 + g_signal;
		i++;
	}
}
