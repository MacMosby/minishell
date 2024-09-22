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

void	free_pipes(t_state *data)
{
	int	i;

	i = 0;
	if(!data->pipes)
		return;
	while (i < data->num_of_processes - 1)
	{
		free(data->pipes[i]);
		i++;
	}
	free(data->pipes);
	data->pipes = NULL;
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

/* iterates over the pipes and closes them */
void	close_pipes(t_state *data)
{
	int	i;

	i = 0;
	while (i < data->num_of_processes - 1)
	{
		close(data->pipes[i][READ_END]);
		close(data->pipes[i][WRITE_END]);
		i++;
	}
}
