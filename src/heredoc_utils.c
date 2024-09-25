/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wel-safa <wel-safa@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 21:03:16 by mrodenbu          #+#    #+#             */
/*   Updated: 2024/09/25 09:33:12 by wel-safa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*clean_hd(char *delim, char *full_line, int flag)
{
	if (flag == 0)
		full_line = ft_join_free(full_line, ft_strdup(""), 0, 0);
	else if (flag == 1)
		full_line = ft_join_free(full_line, ft_strdup("\n"), 0, 0);
	else if (flag == 2)
		full_line = ft_strdup("");
	free(delim);
	delim = NULL;
	return (full_line);
}

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
	delim = ft_strdup(word->content);
	cleanup_shell_exit(state);
	tmp_line = readline(">");
	if (tmp_line == NULL)
		return (clean_hd(delim, full_line, 0));
	while (ft_strncmp(tmp_line, delim, ft_strlen(delim) + 1))
	{
		if (full_line)
			tmp_line = ft_join_free(ft_strdup("\n"), tmp_line, 0, 0);
		else
			full_line = ft_strdup("");
		full_line = ft_join_free(full_line, tmp_line, 0, 0);
		tmp_line = readline(">");
		if (tmp_line == NULL)
			return (clean_hd(delim, full_line, 1));
	}
	if (!full_line)
		return (free(tmp_line), clean_hd(delim, full_line, 2));
	return (free(tmp_line), clean_hd(delim, full_line, 1));
}

/* takes two strings s1 and s2 as inputs, joins them and returns the result
after freeing s1 and s2 */
char	*ft_join_free(char *s1, char *s2, size_t i, size_t j)
{
	char	*str;
	size_t	len;

	if (!s1)
		s1 = ft_strdup("");
	len = ft_strlen(s1) + ft_strlen(s2);
	str = (char *)ft_calloc((len + 1), sizeof(char));
	if (!str)
	{
		free_two_strings(s1, s2);
		exit(1);
	}
	while (i < ft_strlen(s1))
	{
		str[i] = s1[i];
		i++;
	}
	while (j < ft_strlen(s2))
	{
		str[i + j] = s2[j];
		j++;
	}
	free_two_strings(s1, s2);
	return (str);
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
	while (cmd)
	{
		cmd_content = (t_node *) cmd->content;
		iterate_for_heredoc(state, cmd_content, (t_list *) cmd_content->words);
		cmd = cmd->next;
	}
}
