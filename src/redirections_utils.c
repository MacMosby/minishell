/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wel-safa <wel-safa@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 19:53:40 by wel-safa          #+#    #+#             */
/*   Updated: 2024/08/18 19:54:06 by wel-safa         ###   ########.fr       */
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
void	set_fd_out(t_node *curr, char *file, int append)
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
			if (append)
				curr->fd_out = open(file, O_WRONLY | O_APPEND);
			else
				curr->fd_out = open(file, O_WRONLY | O_TRUNC);
		}
	}
}

/*takes string filename and cuts out spaces in beginning and at end
returns 0 on sucess and 1 on error if what's left is an empty string*/
int	filename_cut_spaces(char **filename)
{
	// need to test with filename that is one letter and with empty string filename, etc.
	int	i;
	int	len;

	i = 0;
	while((*filename)[i] == ' ')
		i++;
	*filename = strreplace(filename, NULL, 0, i - 1);
	len = (int) ft_strlen(*filename);
	if (len == 0)
		return (1); // empty string
	i = len - 1;
	while((*filename)[i] == ' ')
	{
		if (i == 0)
			return (1); // empty string
		i--;
	}
	*filename = strreplace(filename, NULL, i + 1, len - 1);
	return (0);
}

/*takes string filename, cuts out spaces in beginning and end and
returns 1 on error and 0 on no error
errors:
1- empty string after expansion
2- more than one word after expansion*/
int		filename_expansion_error(char **filename)
{
	int	i;
	int	sq_flag;
	int	dq_flag;

	sq_flag = 0;
	dq_flag = 0;
	if (!filename)
		return (1);
	if (!(*filename))
		return (1);
	if (!ft_strlen(*filename))
		return (1);
	if (filename_cut_spaces(filename))
		return (1);
	i = 0;
	while((*filename)[i])
	{
		if ((*filename)[i] == '\'' && !dq_flag)
			sq_flag = !sq_flag;
		else if ((*filename)[i] == '\"' && !sq_flag)
			dq_flag = !dq_flag;
		if ((*filename)[i] == ' ' && !sq_flag && !dq_flag)
			return (1);
		i++;
	}
	return (0);
}
