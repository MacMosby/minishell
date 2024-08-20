/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wel-safa <wel-safa@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 13:42:36 by wel-safa          #+#    #+#             */
/*   Updated: 2024/08/20 23:36:17 by wel-safa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*iterates over string word and finds end quote index*/
int	find_end_quote(char *word, int i)
{
	char c;

	c = word[i];
	i++;
	while(word[i] != 0)
	{
		if (word[i] == c)
			return (i);
		i++;
	}
	return (0);
}

/*when it finds a quote, it finds the index of the end of quote
and removes both start and end quote*/
void	removequotes(char **word)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while((*word)[i])
	{
		if ((*word)[i] == '\'' || (*word)[i] == '\"')
		{
			j = find_end_quote(*word, i);
			*word = strreplace(word, NULL, i, i);
			*word = strreplace(word, NULL, j - 1, j - 1);
			i = j - 2; // start from end of word after removing quotes
		}
		i++;
	}
}

/*iterates over list of cmds and list of words in each cmd
and calls removequotes on content of every word*/
void	quotes(t_state *state)
{
	t_list	*cmd;
	t_list	*word;

	cmd = state->cmds;
	while (cmd)
	{
		word = ((t_node *)(cmd->content))->words;
		while(word)
		{
			removequotes((char **) &(word->content));
			word = word->next;
		}
		cmd = cmd->next;
	}
}
