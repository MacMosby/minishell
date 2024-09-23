/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wel-safa <wel-safa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 17:41:31 by wel-safa          #+#    #+#             */
/*   Updated: 2024/09/20 17:05:07 by wel-safa         ###   ########.fr       */
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
	if (!len)
		return (0);
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

int	set_fd_in_single_carrot(t_state *state, t_node *cmd_node, char **filename)
{
	int	fail;

	fail = set_fd_in(state, cmd_node, *filename);
	free(cmd_node->hd_content);
	cmd_node->hd_content = NULL;
	return (fail);
}

/*expands filename and checks for expansion error. Otherwise it removes quotes
from filename and calls set_fd_out and set_fd_in dependiing
on the redirection*/
int	set_fds(t_state *state, t_node *cmd_node, int carrots, char **filename)
{
	char	*og_filename;
	int		fail;

	og_filename = ft_strdup(*filename); // free later
	toexpand(state, filename);
	if (filename_expansion_error(filename)) // This is a redirect error, go to next cmd
	{
		cmd_node->err_flag = 1;
		printf("minishell: %s: ambiguous redirect\n", og_filename);
		return (1); // go to next command
	}
	else
	{
		fail = 0;
		removequotes(filename);
		if (carrots == APPEND)
			fail = set_fd_out(cmd_node, *filename, 1);
		else if (carrots == FD_OUT)
			fail = set_fd_out(cmd_node, *filename, 0);
		else
			fail = set_fd_in_single_carrot(state, cmd_node, filename);
		/* {
			fail = set_fd_in(state, cmd_node, *filename);
			free(cmd_node->hd_content);
			cmd_node->hd_content = NULL;
		} */
	}
	free(og_filename);
	return (fail);
}

/*iterates over list of words in cmd and if heredoc carrots are found,
it copies heredoc content to hd_content variable in command node and sets
fd_in to -1, closing previous fd_in if need be.
for other redirections, it calls set_fds function*/
void	cmd_redirections(t_state *state, t_list *cmd, int carrots)
{
	t_node	*cmd_node;
	t_list	*word;

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
			word = word->next;
		}
		else if (carrots)
		{
			if (set_fds(state, cmd_node, carrots, (char **) &(word->next->content)))
				break ;
			word = word->next;
		}
		if (word)
			word = word->next;
	}
}

/*takes t_state ptr variable and iterates over commands and calls cmd_redirections
function on each. Then it iterates over commands again to delete redirection words
from list of words in each command node*/
void	redirections(t_state *state) // should it be int to return error?
{
	t_list	*cmd;

	cmd = state->cmds;
	while (cmd)
	{
		cmd_redirections(state, cmd, 0);
		cmd = cmd->next;
	}
	cmd = state->cmds;
	while (cmd)
	{
		delete_redirections(&(((t_node *)(cmd->content))->words), NULL, NULL);
		cmd = cmd->next;
	}
}
