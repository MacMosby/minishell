/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wel-safa <wel-safa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 17:41:31 by wel-safa          #+#    #+#             */
/*   Updated: 2024/08/19 20:49:26 by wel-safa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
case 0: NA, returns 0
case 1: >, returns 1
case 2: >>, returns 2
case 3: <, returns 3
case 4: <<, returns 4*/
int	found_carrot(char *str)
{
	size_t	len;

	len = ft_strlen(str);
	if (!ft_strncmp(str, ">", len))
		return (FD_OUT);
	if (!ft_strncmp(str, ">>", len))
		return (APPEND);
	if (!ft_strncmp(str, "<", len))
		return (FD_IN);
	if (!ft_strncmp(str, "<<", len))
		return (HEREDOC);
	return (0);
}

void	set_fds(t_state *state, t_node *cmd_node, int carrots, char **filename)
{
	char	*og_filename;

	og_filename = ft_strdup(*filename); // free later
	toexpand(state, filename);
	if (filename_expansion_error(filename)) // This is a redirect error, go to next cmd
	{
		cmd_node->err_flag = 1;
		printf("minishell: %s: ambiguous redirect\n", og_filename);
		return ; // go to next command
	}
	else
	{
		removequotes(filename);
		if (carrots == APPEND)
			set_fd_out(cmd_node, *filename, 1);
		else if (carrots == FD_OUT)
			set_fd_out(cmd_node, *filename, 0);
		else
		{
			set_fd_in(cmd_node, *filename);
			free(cmd_node->hd_content);
			cmd_node->hd_content = NULL;
		}
	}
	free(og_filename);
}

void	cmd_redirections(t_state *state, t_list *cmd)
{
	t_node	*cmd_node;
	t_list	*word;
	int		carrots;

	cmd_node = (t_node *) cmd->content;
	word = cmd_node->words;
	while (word)
	{
		carrots = found_carrot(word->content);
		if (carrots == HEREDOC)
		{
			cmd_node->hd_content = ft_strdup(word->next->content); // might need to copy this instead because it will be freed later
			if (cmd_node->fd_in > 0)
				close(cmd_node->fd_in);
			cmd_node->fd_in = -1;
		}
		else if (carrots)
			set_fds(state, cmd_node, carrots, (char **) &(word->next->content));
		word = word->next;
	}
}

void	redirections(t_state *state) // should it be int to return error?
{
	t_list	*cmd;

	cmd = state->cmds;
	while (cmd)
	{
		cmd_redirections(state, cmd);
		cmd = cmd->next;
	}
	cmd = state->cmds;
	while (cmd)
	{
		delete_redirections(&(((t_node *)(cmd->content))->words));
		cmd = cmd->next;
	}
}
