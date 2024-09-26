/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wel-safa <wel-safa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 14:45:06 by mrodenbu          #+#    #+#             */
/*   Updated: 2024/09/22 15:36:47 by wel-safa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is_num(char *s)
{
	int	i;

	i = 0;
	if (s[i] == '+' || s[i] == '-')
		i++;
	while (s[i])
	{
		if (!ft_isdigit(s[i]))
			return (0);
		i++;
	}
	return (1);
}

void	clean_exit(t_state *data, int exit_stat, int fd_std_in, int fd_std_out)
{
	if (fd_std_in)
		close(fd_std_in);
	if (fd_std_out)
		close(fd_std_out);
	cleanup_shell_exit(data);
	exit(exit_stat);
}

int	ft_exit(t_state *data, t_node *curr, int fd_std_in, int fd_std_out)
{
	int	exit_status;

	if (curr->args[1] && !curr->args[2])
	{
		if (ft_is_num(curr->args[1]))
		{
			exit_status = ft_atoi(curr->args[1]);
			clean_exit(data, exit_status, fd_std_in, fd_std_out);
		}
		printf("exit\n");
		write(2, "minishell: numeric argument required\n", 37);
		clean_exit(data, 2, fd_std_in, fd_std_out);
	}
	else if (curr->args[1] && curr->args[2])
	{
		write(2, "minishell: too many arguments\n", 30);
		return (1);
	}
	printf("exit\n");
	exit_status = data->exit_status;
	clean_exit(data, exit_status, fd_std_in, fd_std_out);
	return (0);
}
