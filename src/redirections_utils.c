/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wel-safa <wel-safa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 19:53:40 by wel-safa          #+#    #+#             */
/*   Updated: 2024/09/25 21:19:44 by wel-safa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* sets the file descriptor for the infile "file" */
int	set_fd_in(t_state *state, t_node *curr, char *file)
{
	if (access(file, F_OK) == -1)
	{
		curr->err_flag = 1;
		perror("minishell");
		state->exit_status = 1;
		return (1);
	}
	else
	{
		if (access(file, R_OK) == -1)
		{
			curr->err_flag = 1;
			perror("minishell");
		}
		else
		{
			if (curr->fd_in > 0)
				close(curr->fd_in);
			curr->fd_in = open(file, O_RDONLY);
		}
	}
	return (0);
}

/* set the file descriptor for the outfile "file" */
int	set_fd_out(t_node *curr, char *file, int append)
{
	if (!ft_strlen(file))
	{
		curr->err_flag = 1;
		errno = ENOENT;
		perror("minishell");
		return (1);
	}
	if (access(file, F_OK) == -1)
	{
		if (curr->fd_out != STDOUT_FILENO)
			close(curr->fd_out);
		curr->fd_out = open(file, O_WRONLY | O_CREAT, 0644);
	}
	else
	{
		if (access(file, W_OK) == -1)
		{
			curr->err_flag = 1;
			perror("minishell");
			return (1);
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
	return (0);
}

/*takes string filename and cuts out spaces in beginning and at end
returns 0 on sucess and 1 on error if what's left is an empty string*/
int	filename_cut_spaces(char **filename)
{
	int	i;
	int	len;

	i = 0;
	while (ft_isspace((*filename)[i]))
		i++;
	*filename = strreplace(filename, NULL, 0, i - 1);
	len = (int) ft_strlen(*filename);
	if (len == 0)
		return (1);
	i = len - 1;
	while (ft_isspace((*filename)[i]))
	{
		if (i == 0)
			return (1);
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
int	filename_expansion_error(char **filename)
{
	int	i;
	int	sq_flag;
	int	dq_flag;

	sq_flag = 0;
	dq_flag = 0;
	if (!filename || !(*filename))
		return (1);
	if (!ft_strlen(*filename))
		return (1);
	if (filename_cut_spaces(filename))
		return (1);
	i = 0;
	while ((*filename)[i])
	{
		if ((*filename)[i] == '\'' && !dq_flag)
			sq_flag = !sq_flag;
		else if ((*filename)[i] == '\"' && !sq_flag)
			dq_flag = !dq_flag;
		if (ft_isspace((*filename)[i]) && !sq_flag && !dq_flag)
			return (1);
		i++;
	}
	return (0);
}
