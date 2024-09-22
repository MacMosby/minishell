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

/* takes a list object word and its content as the delimiter to the here_doc
implementation which takes several lines of input from the user until a line
is exactly the same as the delimiter and replaces the word content in the list
with the user input exluding the delimiter */
char	*ft_here_doc(t_state *state, t_list *word)
{
	char	*delim;
	char	*tmp_line;
	char	*full_line;

	full_line = NULL;
	delim = word->content;
	tmp_line = readline(">");
	if (tmp_line == NULL)
	{
		full_line = ft_join_free(state, full_line, ft_strdup(""), 0);
		free(word->content);
		word->content = NULL;
		return (full_line);
	}
	while (ft_strncmp(tmp_line, delim, ft_strlen(delim)))
	{
		if (full_line)
		{
			tmp_line = ft_join_free(state, ft_strdup("\n"), tmp_line, 0);
		}
		else
			full_line = ft_strdup("");
		full_line = ft_join_free(state, full_line, tmp_line, 0);
		tmp_line = readline(">");
		if (tmp_line == NULL)
		{
			full_line = ft_join_free(state, full_line, ft_strdup("\n"), 0);
			free(word->content);
			word->content = NULL;
			free(tmp_line);
			return (full_line);
		}
	}
	if (!full_line)
	{
		full_line = ft_strdup("");
		free(word->content);
		free(tmp_line);
		return (full_line);
	}
	full_line = ft_join_free(state, full_line, ft_strdup("\n"), 0);
	free(word->content);
	word->content = NULL;
	free(tmp_line);
	return (full_line);
}

void	fork_for_heredoc(t_state *state, t_node *cmd, t_list *curr)
{
	int		fd[2];
	int		pid;
	int		wstatus;
	char	*hd_output;
	int		len_out;

	if (pipe(fd) == -1)
		error_exit(state);
	pid = fork();
	if (pid == -1)
		error_exit(state);
	if (pid == 0)
	{
		setup_heredoc_signals_child();
		hd_output = NULL;
		hd_output = ft_here_doc(state, curr);
		len_out = ft_strlen(hd_output) + 1;
		close(fd[READ_END]);
		write(fd[WRITE_END], &len_out, sizeof(int));
		write(fd[WRITE_END], hd_output, len_out);
		close(fd[WRITE_END]);
		free(hd_output);
		cleanup_shell_exit(state);
		exit (0);
	}
	else
	{
		close(fd[WRITE_END]);
		waitpid(pid, &wstatus, 0);
		//if (waitpid(pid, &wstatus, 0) == -1)
			//printf("What to do if waitpid for hd child fails?\n");
		if (g_signal)
			cmd->err_flag = 128 + g_signal;
			// if we don't run through the heredoc we need to
			// delete the EOF from the word list
		else
		{
			read(fd[READ_END], &len_out, sizeof(int));
			hd_output = malloc(len_out * sizeof(char));
			if (!hd_output)
				error_exit(state);
			if (read(fd[READ_END], hd_output, len_out * sizeof(char)) < 0)
				printf("read function fails\n");
			close(fd[READ_END]);
			free(curr->content);
			curr->content = hd_output;
		}
	}
}

/*iterates over list of words in cmd and if heredoc carrots are found,
it checks the next word i.e. delimiter and sets hd_expand_flag
in t_node cmd_content if quotes are found in delimiter.
Then it calls removequotes function on the delimiter, and
calls ft_here_doc with the delimiter.*/
void	get_heredoc_input(t_state *state, t_node *cmd_content, t_list *words)
{
	t_list	*curr;
	int		i;
	char	*delim;

	i = 0;
	curr = words;
	while (curr)
	{
		if (ft_strncmp(curr->content, "<<", 2) == 0)
		{
			curr = curr->next;
			if (curr)
			{
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
			else
				return ;
		}
		curr = curr->next;
	}
}

/*takes t_state variable state and iterates over t_list variable cmds
calls get_here_doc_input on t_node cmd_content
and list of words in the node cmd_content*/
void	heredoc_in(t_state *state)
{
	t_list	*cmd;
	t_node	*cmd_content;

	cmd = state->cmds;
	if (!cmd)
		return ;
	// is the next line necessary? three lines later we do the same!?
	cmd_content = (t_node *) cmd->content;
	while (cmd)
	{
		cmd_content = (t_node *) cmd->content;
		//print_list(cmd_content->words);
		get_heredoc_input(state, cmd_content, (t_list *) cmd_content->words);
		cmd = cmd->next;
	}
}

/*iterates over hd_content variable and calls expand function if $ sign is found
with hd_flag = 1*/
void	heredoc_expansions(t_state *state, char **hd_content)
{
	int	i;

	i = 0;
	if (!hd_content)
		return ;
	if (!(*hd_content))
		return ;
	while ((*hd_content)[i])
	{
		if ((*hd_content)[i] == '$')
			i = expand(state, hd_content, i, 1);
		i++;
	}
}
