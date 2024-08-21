/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wel-safa <wel-safa@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 14:03:48 by mrodenbu          #+#    #+#             */
/*   Updated: 2024/08/21 22:08:20 by wel-safa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_for_builtin(char *cmd, char **builtins)
{
	int	i;

	i = 0;
	while (i < 7)
	{
		if (ft_strncmp(cmd, builtins[i], ft_strlen(builtins[i])) == 0)
			return (1);
		i++;
	}
	return (0);
}

int	check_for_dir(char *str)
{
	struct stat path_stat;

	if (ft_strchr(str, '/'))
	{
		if (access(str, F_OK) == 0)
		{
			if (stat(str, &path_stat) == - 1)
			{
				// print some error ???
			}
			else
			{
				if (S_ISDIR(path_stat.st_mode))
					return (1);
				else
					return (0);
			}
		}
	}
	return (0);
}

void	handle_cmd(t_state *data, t_node *curr, char *str)
{
	if (!str)
		curr->cmd_flag = NO_CMD;
	else if (check_for_builtin(str, data->builtins))
	{
		curr->cmd = str;
		curr->cmd_flag = BUILTIN;
	}
	else if (check_for_dir(str))
	{
		curr->err_flag = CMD_ERR;
		printf("??? minishell: %s: Is a directory\n", str);
	}
	else if (access(str, F_OK) == 0)
	{
		// check if directory
		if (access(str, X_OK) == 0)
		{
			curr->cmd = str;
			curr->cmd_flag = PATH;
		}
		else
		{
			// exit status has to be 126
			curr->err_flag = CMD_ERR;
			printf("??? minishell: %s: Permission denied\n", str);
		}
	}
	else if (get_path(data, str))
	{
		curr->cmd = get_path(data, str);
		curr->cmd_flag = PATH;
	}
	else
	{
		// exit status has to be 127 -
		curr->err_flag = CMD_ERR;
		printf("??? minishell: %s: Command not found\n", str);
	}
}

void	cmd_loop(t_state *state)
{
	t_list	*cmd;
	char	*str;
	
	cmd = state->cmds;
	while (cmd)
	{
		str = ((t_node *)cmd->content)->words->content;
		handle_cmd(state, (t_node *)cmd->content, str);
		wordlist_to_cmdarr((t_node *)cmd->content);
		cmd = cmd->next;
	}
	state->num_of_processes = ft_lstsize(state->cmds);
}
