/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wel-safa <wel-safa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 19:26:09 by wel-safa          #+#    #+#             */
/*   Updated: 2024/09/20 17:39:21 by wel-safa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* takes word and two string pointers which it assigns substrings from word
from index 0 to i and from index j+1 to len,
disregarding chars between i and j*/
void	substr_words(char **first, char **second, char *word, int i, int j)
{
	int	len;

	len = ft_strlen(word);
	*first = ft_substr(word, 0, i);
	*second = ft_substr(word, j + 1, len); // len? or len-j should be okay but check with other situations
}

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

	// change to strjoin free function instead
	if (j < i)
		return (*word);
	substr_words(&first, &second, *word, i, j);
	if (!rep)
	{
		res = ft_strjoin(first, second);
		free(first);
		free(second);
		free(*word);
		return (res);
	}
	tmp = ft_strjoin(first, rep);
	res = ft_strjoin(tmp, second);
	free(first);
	free(second);
	free(tmp);
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

/*takes t_state struct and string pointer word and index i of the dollar sign found
and hd_flag that signifies if it is a heredoc expansion or not.
It finds variable after $ sign.
if var is found, it searches env for var and replaces $VAR from word with its value
otherwise it removes $VAR from word.
if variable is not found, no expansions happen.
except when hd_flag is 0 AND in such cases: $"hello" or $'hello'
where the dollar sign is removed.
it returns index last character (replacement or no replacement)
*/
int	expand(t_state *state, char **word, int i, int hd_flag)
{
	int		j;
	char	*var;
	int		len;
	char	*rep;

	j = i + 1;
	var = NULL;
	// MARC START
	// what if $? ??? --> var_letter returns 0 even though it should not
	/* if (ft_strncmp("$?", *word, 2) == 0)
	{
		*word = ft_strdup(ft_itoa(state->exit_status));
		return (i - 1 + ft_strlen(ft_itoa(state->exit_status)));
	} */
	// MARC END
	while ((*word)[j])
	{
		// MARC START
		if ((*word)[j] == '?' && (j - i == 1))
		{
			*word = strreplace(word, ft_itoa(state->exit_status), i, j);
			return (i - 1 + ft_strlen(ft_itoa(state->exit_status)));
		}
		// MARC END
		if (ft_isdigit((*word)[j]) && (j - i == 1))
		{
			*word = strreplace(word, NULL, i, i + 1);
			return (i - 1);
		}
		if (var_letter((*word)[j]) == 0)
			break ; // end of var and j is index after var
		j++;
	}
	len = j - i - 1; // length of variable name
	if (len > 0)
	{
		var = (char *)malloc((len + 1) * sizeof(char));
		if (!var)
			error_exit(state);
		// copy var from word.
		ft_memcpy(var, (*word) + i + 1, len);
		var[len] = '\0';
		rep = find_var_value(state, var);
		if (!rep)
			rep = ""; // handle when var is not found
		*word = strreplace(word, rep, i, i + len);
		// index change to after replacement
		//  - 1, it will iterate to the next character after this function.
		i += ft_strlen(rep) - 1;
		free(var);
	}
	else if (!hd_flag && ((*word)[j] == '\"' || (*word)[j] == '\''))
	{
		// $"hello" or $'hello' removes the dollar sign
		// it will not detect "hello $" as this is taken care of in toexpand function if statement
		*word = strreplace(word, NULL, i, i);
		i -= 1;
	}
	return (i);
}

/*takes t_state struct and a string pointer of the word,
it detects whether $ is inside double or single quotes
it expands $VAR for normal state or if it is inside double quote
and there is a variable. If there is no variable or
it is inside the single quote it will not expand
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
				// not inside any quotes
				// find variable to expand
				// Variable cuts off at char that is not alphanumric or not an underscore.
				// if quote is right after $ sign there will be no var
				// and nothing to expand, just remove $ sign
				i = expand(state, word, i, 0);
			else if (dq_flag && (*word)[i + 1] != '\"')
				// inside double quotes AND there is a VAR assigned after $
				// for example "hello $ " or "hello $",
				// will be ignored and kept in the word
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
