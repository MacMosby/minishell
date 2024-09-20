/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrodenbu <mrodenbu@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 14:37:21 by mrodenbu          #+#    #+#             */
/*   Updated: 2024/09/20 14:37:24 by mrodenbu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* takes an input string and changes the current working directory to the path given as string */
int	ft_cd(t_state *state, t_node *curr)
{
	int		errno;
	char	*old_pwd;
	char	*pwd;

	old_pwd = ft_strjoin("OLDPWD=", getcwd(NULL, 0));
	if (curr->args[1] && !curr->args[2])
	{
		if (chdir(curr->args[1]) == -1)
		{
			if (errno == 2)
				perror(" ");
			return (1);
		}
		else
		{
			pwd = ft_strjoin("PWD=", getcwd(NULL, 0));
			do_export(state, pwd);
			do_export(state, old_pwd);
		}
	}
	else if (curr->args[1] && curr->args[2])
	{
		write(2, " too many arguments\n", 20);
		return (1);
	}
	return (0);
}
