/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wel-safa <wel-safa@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 15:45:10 by mrodenbu          #+#    #+#             */
/*   Updated: 2024/08/21 22:31:01 by wel-safa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_pipes(t_state *data)
{
	int	i;

	i = 0;
	while (i < data->num_of_processes - 1)
	{
		free(data->pipes[i]);
		i++;
	}
}

/* initializes pipes and store them in the data struct */
void	init_pipes(t_state *data)
{
	int	i;

	//create pipe array of arrays
	if (data->num_of_processes < 2)
	{
		data->pipes = NULL;
		return;
	}
	data->pipes = (int **)malloc((data->num_of_processes - 1) * sizeof(int*));
	if (!data->pipes)
		// EXIT HANDLE
		exit(1);
	i = 0;
	while (i < data->num_of_processes - 1)
	{
		data->pipes[i] = (int *)malloc(2 * sizeof(int));
		if (!data->pipes[i])
			// EXIT HANDLE
			exit(2);
		if (pipe(data->pipes[i]) == -1)
			// EXIT HANDLE
			exit(3);
		i++;
	}
}

/* creates the data structure for the array of process IDs */
void	init_pids(t_state *data)
{
	data->pids = (int *)malloc(data->num_of_processes * sizeof(int));
	if (!data->pids)
		// EXIT HANDLE
		exit(1);
}

/* creates the redirections to pipes before looking for infiles/outfiles */
void	redirect_to_pipes(t_state *data, int i)
{
	// don't pipe to next pipe in case of error
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

/* iterates over PIDs to wait for all the child processes to finish */
void	wait_loop(t_state *data)
{
	int	i;
	int	wstatus;

	i = 0;
	while (i < data->num_of_processes)
	{
		// do we need to replace NULL or 0 ?
		if (waitpid(data->pids[i], &wstatus, 0) == -1)
		{
			// EXIT HANDLER ???
			if (data->exit_status)
				exit(data->exit_status);
			exit (1);
			//printf("WE GET HERE IF WAITPID FAILS (ctrl-c  or ctrl-\\on execution)- WHAT TO DO HERE?\n");
		}
		if (WIFEXITED(wstatus)) // if this is true, the process terminated normally
		{
			// exit status for cmd not found is 127
			// if cmd found but not executable, exit status is 126
			// do we have to set them manually or will the return of waitpid be perfect to just use N + 128 ???
			data->exit_status = WEXITSTATUS(wstatus);
			/* if (data->exit_status == 0)
				printf("Process %d with pid %d: Success!\n", i, data->pids[i]);
			else
			{
				data->exit_status += 128;
				printf("Process %d with pid %d: Failure with status code %d\n", i, data->pids[i], data->exit_status);
			} */
		}
		/* else
		{
			printf("What is the issues here in process %d\n", i);
			printf("status is %d\n", wstatus);
		} */
		i++;
	}
	//printf("End of program: exit status: %d\n", data->exit_status);
}
