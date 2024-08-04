/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wel-safa <wel-safa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 13:42:36 by wel-safa          #+#    #+#             */
/*   Updated: 2024/08/04 20:51:19 by wel-safa         ###   ########.fr       */
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

/*iterates over list of words and calls removequotes on content of every word
it skips heredoc delim*/
void	quotes(t_state *state)
{
	t_list	*word;
	//t_list	*before;

	word = state->words;
	//before = word;
	while(word)
	{
		//if(ft_strncmp((char *) before->content, "<<", ft_strlen((char *) before->content)))
		removequotes((char **) &(word->content));
		//before = word;
		word = word->next;
	}
}