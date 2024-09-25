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

void	change_directory(t_state *state)
{
	char	*cwd;
	char	*pwd;
	char	*old_pwd;

	cwd = getcwd(NULL, 0);
	old_pwd = ft_strjoin("OLDPWD=", cwd);
	pwd = ft_strjoin("PWD=", cwd);
	do_export(state, pwd, 0);
	do_export(state, old_pwd, 0);
	free(old_pwd);
	free(pwd);
	free(cwd);
}

/* takes an input string and changes the current working directory to the path
given as string */
int	ft_cd(t_state *state, t_node *curr)
{
	if (curr->args[1] && !curr->args[2])
	{
		if (chdir(curr->args[1]) == -1)
		{
			perror("minishell");
			return (1);
		}
		else
			change_directory(state);
	}
	else if (curr->args[1] && curr->args[2])
	{
		write(2, "minishell: too many arguments\n", 30);
		return (1);
	}
	return (0);
}
