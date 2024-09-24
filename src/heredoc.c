/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wel-safa <wel-safa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 19:21:09 by wel-safa          #+#    #+#             */
/*   Updated: 2024/09/22 16:10:27 by wel-safa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	heredoc_child(t_state *state, t_list *curr, int *fd)
{
	char	*hd_output;
	int		len;

	setup_heredoc_signals_child();
	hd_output = NULL;
	hd_output = ft_here_doc(state, curr);
	len = ft_strlen(hd_output) + 1;
	close(fd[READ_END]);
	write(fd[WRITE_END], &len, sizeof(int));
	write(fd[WRITE_END], hd_output, len);
	close(fd[WRITE_END]);
	free(hd_output);
	exit (0);
}

void	heredoc_parent(t_state *state, t_list *curr, int *fd)
{
	char	*hd_output;
	int		len;

	hd_output = NULL;
	read(fd[READ_END], &len, sizeof(int));
	hd_output = malloc(len * sizeof(char));
	if (!hd_output)
		error_exit(state);
	read(fd[READ_END], hd_output, len * sizeof(char));
	free(curr->content);
	curr->content = hd_output;
}

void	fork_for_heredoc(t_state *state, t_node *cmd, t_list *curr)
{
	int		fd[2];
	int		pid;
	int		wstatus;

	if (pipe(fd) == -1)
		error_exit(state);
	pid = fork();
	if (pid == -1)
		error_exit(state);
	if (pid == 0)
		heredoc_child(state, curr, fd);
	else
	{
		waitpid(pid, &wstatus, 0);
		if (g_signal)
			cmd->err_flag = 128 + g_signal;
		else
			heredoc_parent(state, curr, fd);
		close(fd[WRITE_END]);
		close(fd[READ_END]);
	}
}

void	get_heredoc_input(t_state *state, t_node *cmd_content, t_list *curr)
{
	char	*delim;
	int		i;

	i = 0;
	delim = (char *) curr->content;
	if (cmd_content)
	{
		while (delim[i])
		{
			if (delim[i] == '\'' || delim[i] == '\"')
			{
				cmd_content->hd_expand_flag = 0;
				break ;
			}
			i++;
		}
	}
	removequotes((char **) &(curr->content));
	fork_for_heredoc(state, cmd_content, curr);
}

/*iterates over list of words in cmd and if heredoc carrots are found,
it checks the next word i.e. delimiter and sets hd_expand_flag
in t_node cmd_content if quotes are found in delimiter.
Then it calls removequotes function on the delimiter, and
calls ft_here_doc with the delimiter.*/
void	iterate_for_heredoc(t_state *state, t_node *cmd_content, t_list *words)
{
	t_list	*curr;

	curr = words;
	while (curr)
	{
		if (ft_strncmp(curr->content, "<<", 2) == 0)
		{
			curr = curr->next;
			if (curr)
				get_heredoc_input(state, cmd_content, curr);
			else
				return ;
		}
		curr = curr->next;
	}
}
