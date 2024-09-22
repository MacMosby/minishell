/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_pipes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrodenbu <mrodenbu@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 18:57:18 by mrodenbu          #+#    #+#             */
/*   Updated: 2024/09/22 18:57:20 by mrodenbu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_pipes(t_state *data)
{
	int	i;

	i = 0;
	if (!data->pipes)
		return ;
	while (i < data->num_of_processes - 1)
	{
		free(data->pipes[i]);
		i++;
	}
	free(data->pipes);
	data->pipes = NULL;
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
