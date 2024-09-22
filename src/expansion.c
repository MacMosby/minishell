/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wel-safa <wel-safa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 19:26:09 by wel-safa          #+#    #+#             */
/*   Updated: 2024/09/22 20:28:36 by wel-safa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* takes word and two string pointers which it assigns substrings from word
from index 0 to i and from index j+1 to len,
disregarding chars between i and j*/
/*void	substr_words(char **first, char **second, char *word, int i, int j)
{
	int	len;

	len = ft_strlen(word);
	*first = ft_substr(word, 0, i);
	*second = ft_substr(word, j + 1, len); 
	// len? or len-j should be okay but check with other situations
}*/

/* takes a string: word, cuts out the part from i to j
and replaces it with another string: rep
if rep = "" or NULL, the characters between i and j are cut out
the new string is returned*/
char	*strreplace(char **word, char *rep, int i, int j)
{
	char	*first;
	char	*second;
	char	*tmp;
	char	*res;

	if (j < i)
		return (*word);
	first = ft_substr(*word, 0, i);
	second = ft_substr(*word, j + 1, ft_strlen(*word));
	if (!rep)
		res = ft_strjoin(first, second);
	else
	{
		tmp = ft_strjoin(first, rep);
		res = ft_strjoin(tmp, second);
		free(tmp);
	}
	free(first);
	free(second);
	free(*word);
	return (res);
}

/*returns 1 if c is alphanumeric or underscore, returns 0 otherwise*/
int	var_letter(char c)
{
	if (ft_isalnum(c) || c == '_')
		return (1);
	return (0);
}

/*takes t_state struct and a string pointer of the word,
it detects whether $ is inside double or single quotes
it expands $VAR for normal state or if it is inside double quote
and there is a variable. If there is no variable or
it is inside the single quote it will not expand
VAR cuts off at char that is not alphanumric or not an underscore.
if quote is right after $ sign, the result is removing the $ sign.
*/
void	toexpand(t_state *state, char **word)
{
	int	sq_flag;
	int	dq_flag;
	int	i;

	sq_flag = 0;
	dq_flag = 0;
	i = 0;
	while ((*word)[i])
	{
		if ((*word)[i] == '\'' && !dq_flag)
			sq_flag = !sq_flag;
		else if ((*word)[i] == '\"' && !sq_flag)
			dq_flag = !dq_flag;
		else if ((*word)[i] == '$')
		{
			if (!sq_flag && !dq_flag && (*word)[i + 1] != 0)
				i = expand(state, word, i, 0);
			else if (dq_flag && (*word)[i + 1] != '\"')
				i = expand(state, word, i, 0);
		}
		i++;
	}
}

void	delete_empty_words(t_list *cmd)
{
	t_list	*word;
	t_list	*before;
	t_list	*after;

	word = ((t_node *)cmd->content)->words;
	before = NULL;
	while (word)
	{
		after = word->next;
		if (ft_strlen((char *) word->content) == 0)
		{
			free(word->content);
			free(word);
			if (before)
				before->next = after;
			else
				((t_node *)cmd->content)->words = after;
			word = after;
		}
		else
		{
			before = word;
			word = word->next;
		}
	}
}

/*takes state struct and iterates over list of words in each cmd
and calls toexpand function on each and then calls heredoc_expansions function
on hd_content of each command*/
void	expansion(t_state *state)
{
	t_list	*cmd;
	t_list	*word;

	cmd = state->cmds;
	while (cmd)
	{
		word = ((t_node *)cmd->content)->words;
		while (word)
		{
			toexpand(state, (char **) &(word->content));
			word = word->next;
		}
		if (((t_node *)cmd->content)->hd_expand_flag)
			heredoc_expansions(state, &(((t_node *)cmd->content)->hd_content));
		delete_empty_words(cmd);
		cmd = cmd->next;
	}
}
