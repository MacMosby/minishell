/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wel-safa <wel-safa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 19:21:09 by wel-safa          #+#    #+#             */
/*   Updated: 2024/09/15 21:47:53 by wel-safa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* takes two strings s1 and s2 as inputs, joins them and returns the result
after freeing s1 and s2 */
char	*ft_join_free(char *s1, char *s2)
{
	char	*str;
	size_t	len;
	size_t	i;
	size_t	j;

	if (!s1)
		s1 = ft_strdup("");
	len = ft_strlen(s1) + ft_strlen(s2);
	str = (char *)malloc(len + 1);
	if (!str)
		return (NULL);
	i = 0;
	while (i < ft_strlen(s1))
	{
		str[i] = s1[i];
		i++;
	}
	j = 0;
	while (j < ft_strlen(s2))
	{
		str[i + j] = s2[j];
		j++;
	}
	free(s1);
	free(s2);
	str[i + j] = 0;
	return (str);
}

/* takes a list object word and its content as the delimiter to the here_doc
implementation which takes several lines of input from the user until a line
is exactly the same as the delimiter and replaces the word content in the list
with the user input exluding the delimiter */
char	*ft_here_doc(t_list *word)
{
	char	*delim;
	char	*tmp_line;
	char	*full_line;

	full_line = NULL;
	delim = word->content;
	tmp_line = readline(">");
	// MARC START
	if (tmp_line == NULL)
	{
		// Ctl-D (EOF) handle
		printf("TEST TEST HD\n");
		//return ;
		full_line = ft_join_free(full_line, ft_strdup("\n"));
		free(word->content);
		word->content = NULL;
		return (full_line);
	}
	// MARC END
	while (ft_strncmp(tmp_line, delim, ft_strlen(delim)))
	{
		if (full_line)
		{
			tmp_line = ft_join_free(ft_strdup("\n"), tmp_line);
		}
		else
			full_line = ft_strdup("");
		full_line = ft_join_free(full_line, tmp_line);
		tmp_line = readline(">");
		// MARC START
		if (tmp_line == NULL)
		{
			// Ctl-D (EOF) handle
			printf("ctrl-D in HD\n");
			//return ;
			full_line = ft_join_free(full_line, ft_strdup("\n"));
			free(word->content);
			word->content = NULL;
			free(tmp_line);
			return (full_line);
		}
		// MARC END
	}
	if (!full_line)
	{
		full_line = ft_strdup("\n");
		free(word->content);
		free(tmp_line);
		return (full_line);
	}
	full_line = ft_join_free(full_line, ft_strdup("\n"));
	free(word->content);
	word->content = NULL;
	free(tmp_line);
	//word->content = full_line;
	return (full_line);
}

void	fork_for_heredoc(t_node *cmd, t_list *curr)
{
	int		fd[2];
	int		pid;
	int		wstatus;
	char	*hd_output;

	if (pipe(fd) == -1)
		// EXIT HANDLE
		exit (1);
	pid = fork();
	if (pid == -1)
		// EXIT HANDLE
		exit (1);
	if (pid == 0)
	{
		// CHILD PROCESS
		setup_heredoc_signals_child();
		char	*hd_input = NULL;
		int		len;

		hd_input = ft_here_doc(curr);
		len = ft_strlen(hd_input) + 1;
		close(fd[READ_END]);

		write(fd[WRITE_END], &len, sizeof(int));
		write(fd[WRITE_END], hd_input, len);
		close(fd[WRITE_END]);
		//curr->content = ft_strdup(hd_input);
		//printf("heredoc input: %s\n", hd_input);
		exit (0);
	}
	else
	{
		// PARENT PROCESS

		int		len;

		close(fd[WRITE_END]);
		waitpid(pid, &wstatus, 0);
		//if (waitpid(pid, &wstatus, 0) == -1)
			// what to do if waitpid fails ???
			//printf("What to do if waitpid for hd child fails?\n");
		if (g_signal == 0)
		{
			read(fd[READ_END], &len, sizeof(int));
			hd_output = malloc(len * sizeof(char));
			if (read(fd[READ_END], hd_output, len * sizeof(char)) < 0)
				printf("read function fails\n");
			close(fd[READ_END]);
			free(curr->content);
			curr->content = hd_output;
		}
		else
		{
			cmd->err_flag = 130;
			// if we don't run through the heredoc we need to
			// delete the EOF from the word list
		}
	}
}

/*iterates over list of words in cmd and if heredoc carrots are found,
it checks the next word i.e. delimiter and sets hd_expand_flag
in t_node cmd_content if quotes are found in delimiter.
Then it calls removequotes function on the delimiter, and
calls ft_here_doc with the delimiter.*/
void	get_heredoc_input(t_node *cmd_content, t_list *words)
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
			// what if "<<" is the last word ?
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
							break;
						}
						i++;
					}
				}
				removequotes((char **) &(curr->content));
				fork_for_heredoc(cmd_content, curr);
				//ft_here_doc(curr);
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
void	heredoc_in(t_state * state)
{
	t_list	*cmd;
	t_node	*cmd_content;
	//int		pid;
	//int		wstatus;

	cmd = state->cmds;
	// MARC START
	if (!cmd)
		return ;
	// MARC END
	// is the next line necessary? three lines later we do the same!?
	cmd_content = (t_node *) cmd->content;
	while (cmd)
	{
		cmd_content = (t_node *) cmd->content;
		//print_list(cmd_content->words);
		get_heredoc_input(cmd_content, (t_list *) cmd_content->words);
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
		return;
	if (!(*hd_content))
		return;
	while ((*hd_content)[i])
	{
		if ((*hd_content)[i] == '$')
			i = expand(state, hd_content, i, 1);
		i++;
	}
}
