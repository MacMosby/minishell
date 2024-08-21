/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wel-safa <wel-safa@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 17:25:02 by mrodenbu          #+#    #+#             */
/*   Updated: 2024/08/21 21:08:46 by wel-safa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* redirects the input and output of the cmd to pipes and/or files */
void	redirect_in_out(t_state *data, t_node *curr, int i)
{
	int	fd[2];

	// redirect to pipes initially
	redirect_to_pipes(data, i);
	// redirect to infiles/outfiles if we have them set
	if (curr->fd_in != STDIN_FILENO)
	{
		if (curr->fd_in == -1)
		{
			if (pipe(fd) == -1)
				// EXIT HANDLE
				exit(1);
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
	if (curr->fd_out != STDOUT_FILENO)
	{
		dup2(curr->fd_out, STDOUT_FILENO);
		close(curr->fd_out);
	}
}



/* creates a child process and executes the command */
void	fork_executor(t_state *data, t_node *curr, int i)
{
	data->pids[i] = fork();
	if (data->pids[i] == -1)
		// EXIT HANDLE
		exit(1);
	if (data->pids[i] == 0)
	{
		// redirect to pipes, infiles and outfiles
		redirect_in_out(data, curr, i);
		// close pipes
		close_pipes(data);
		// if we have a correct cmd and NOT NULL
		if (curr->err_flag == CMD_OK && curr->cmd)
		{
			if (curr->cmd_flag == PATH)
			{
				// NOT THE RIGHT POSITION IN THE END, ONLY FOR NOW
				// what about absolute and relative paths ???
				//curr->cmd = get_path(data, curr->cmd);
				// execution of process
				//if (execlp(curr->cmd, curr->args, NULL) == -1)
				if (execve(curr->cmd, curr->args, data->env) == -1)
					// error handle here
					// EXIT HANDLE
					exit(2);
			}
			else if (curr->cmd_flag == BUILTIN)
				invoke_builtin(data, curr);
		}
	}
	// EXIT HANDLE
	//exit(3);
}

/* iterates over list of commands and executes them one by one */
void	execution_loop(t_state *data)
{
	t_list	*curr;
	int	i;

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

/* iterate over the linked list and executes the commands one by one */
void	executor(t_state *data)
{
	// initialize pipe array of array
	init_pipes(data);
	// initialize array of process IDs
	init_pids(data);
	execution_loop(data);
	wait_loop(data);
	// exit status ?
	// cleanup missing
}
