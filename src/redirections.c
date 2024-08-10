/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wel-safa <wel-safa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 17:41:31 by wel-safa          #+#    #+#             */
/*   Updated: 2024/08/10 17:52:55 by wel-safa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* sets the file descriptor for the infile "file" */
void	set_fd_in(t_node *curr, char *file)
{
	if (access(file, F_OK) == -1)
	{
		// ERROR FILE DOES NOT EXIST
		curr->err_flag = 1;
		printf("??? minishell: %s: No such file or directory\n", file);
	}
	else
	{
		if (access(file, R_OK) == -1)
		{
			// ERROR NOT READABLE
			curr->err_flag = 1;
			printf("??? minishell: %s: Permission denied\n", file);
		}
		else
		{
			if (curr->fd_in != STDIN_FILENO)
				close(curr->fd_in);
			curr->fd_in = open(file, O_RDONLY);
		}
	}
}

/* set the file descriptor for the outfile "file" */
void	set_fd_out(t_node *curr, char *file)
{
	if (access(file, F_OK) == -1)
	{
		curr->fd_out = open(file, O_WRONLY | O_CREAT);
	}
	else
	{
		if (access(file, W_OK) == -1)
		{
			// ERROR FILE NOT WRITABLE
			curr->err_flag = 1;
			printf("??? minishell: %s: Permission denied\n", file);
		}
		else
		{
			if (curr->fd_out != STDOUT_FILENO)
				close(curr->fd_out);
			if (curr->append)
				curr->fd_out = open(file, O_WRONLY | O_APPEND);
			else
				curr->fd_out = open(file, O_WRONLY | O_TRUNC);
		}
	}
}

void	redirections(t_state *state) // should it be int to return error?
{
	t_list	*cmd;
	t_list	*word;
	
	cmd = state->cmds;
	while (cmd)
	{
		word = ((t_node *) cmd->content)->words;
		while (word)
		{
			if (ft_strncmp(word->content, ">>", 2))
			{
				((t_node *) cmd->content)->append = 1;
				set_fd_out((t_node *) cmd->content, word->next->content);
			}
			word = word->next;
		}
	}
}