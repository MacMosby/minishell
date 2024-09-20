/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrodenbu <mrodenbu@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 14:45:06 by mrodenbu          #+#    #+#             */
/*   Updated: 2024/09/20 14:45:08 by mrodenbu         ###   ########.fr       */
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

// needs to work with arguments ???
void	ft_exit(t_state *data, t_node *curr)
{
	printf("exit\n");
	if (curr->args[1] && !curr->args[2])
	{
		if (ft_is_num(curr->args[1]))
			exit(ft_atoi(curr->args[1]));
		write(2, " numeric argument required\n", 27);
		// EXIT HANDLE
		// MARC START
		cleanup_shell_exit(data);
		// MARC END
		exit (2);
	}
	else if (curr->args[1] && curr->args[2])
	{
		write(2, " too many arguments\n", 20);
		// EXIT HANDLE
		// MARC START
		cleanup_shell_exit(data);
		// MARC END
		exit (1);
	}
	// EXIT HANDLE
	// MARC START
	cleanup_shell_exit(data);
	// MARC END
	exit (0);
}
