/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wel-safa <wel-safa@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 17:53:07 by mrodenbu          #+#    #+#             */
/*   Updated: 2024/09/18 00:28:04 by wel-safa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* routes to the needed builtin function and calls it */
int	invoke_builtin(t_state *data, t_node *curr)
{
	if (ft_strncmp(curr->cmd, "echo", 5) == 0)
		return (ft_echo(curr->args));
	else if (ft_strncmp(curr->cmd, "cd", 3) == 0)
		return (ft_cd(data, curr));
	else if (ft_strncmp(curr->cmd, "pwd", 4) == 0)
		return (ft_pwd());
	else if (ft_strncmp(curr->cmd, "export", 7) == 0)
		return (ft_export(data, curr));
	else if (ft_strncmp(curr->cmd, "unset", 6) == 0)
		return (ft_unset(data, curr));
	else if (ft_strncmp(curr->cmd, "env", 4) == 0)
		ft_env(data);
	else if (ft_strncmp(curr->cmd, "exit", 5) == 0)
		ft_exit(data, curr);
	// what should be the return value ?
	return (1);
}
