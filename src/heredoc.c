/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wel-safa <wel-safa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 19:21:09 by wel-safa          #+#    #+#             */
/*   Updated: 2024/08/10 17:09:00 by wel-safa         ###   ########.fr       */
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
void	ft_here_doc(t_list *word)
{
	char	*delim;
	char	*tmp_line;
	char	*full_line;

	full_line = NULL;
	delim = word->content;
	tmp_line = readline(">");
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
	}
	if (!full_line)
		full_line = ft_strdup("");
	free(word->content);
	free(tmp_line);
	word->content = full_line;
}

void	get_here_doc_input(t_list *words)
{
	t_list *curr;

	curr = words;
	while (curr)
	{
		if (ft_strncmp(curr->content, "<<", 2) == 0)
		{
			// what if "<<" is the last word ?
			curr = curr->next;
			if (curr)
				ft_here_doc(curr);
		}
		curr = curr->next;
	}
}

void	heredoc_in(t_state * state)
{
	t_list *cmd;
	t_node	*cmd_content;

	cmd = state->cmds;
	cmd_content = (t_node *) cmd->content;
	while (cmd)
	{
		cmd_content = (t_node *) cmd->content;
		//print_list(cmd_content->words);
		get_here_doc_input((t_list *) cmd_content->words);
		cmd = cmd->next;
	}
}

// void getheredocin(t_list *words); // gets list of words per cmd
/*iterate over list. Once it finds <<, it will prompt the user for input, 
using delim to end the input, and then replace the delimitor content.
free(delim)
assign delim list item->content = new heredoc input
*/