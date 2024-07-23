/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_handler_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wel-safa <wel-safa@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 20:54:36 by wel-safa          #+#    #+#             */
/*   Updated: 2024/07/23 20:57:14 by wel-safa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*takes t_state struct and index 'start' that points to the carrot character
counts how many carrots are after
if more than two carrots is encountered, it exits with Syntax error
else it returns number of carrots*/
int	carrotcount(t_state *state, int start)
{
	char	c;
	int		end;

	c = state->input[start];
	end = start;
	while (state->input[end] == c)
		end++;
	if (end - start > 2)
	{
		// more than three carrots
		// error, handle exit and cleanup
		exit (1);
	}
	else if (end - start == 2)
		return (2); // two carrots
	return (1); // only one carrot
}

/*takes index of start of word i 
and finds the end i.e. (|, , >, <) or end of string
returns end of word character index*/
int	find_word_end(t_state *state, int i)
{
	char c;

	while (c = state->input[i])
	{
		while (c == '\'' || c == '\"')
		{
			i = find_closed_quote(state, i, c) + 1;
			c = state->input[i];
		}
		if (c == '|' || c == ' ' || c == '>' || c == '<')
		{
			// end of file name or word
			return (i - 1); // return end of file name or word
		}
		i++;
	}
	return (i - 1); // end of string, returns index before NULL
}

/*takes index i of start of quotes
and takes the quote whether double or single as character c
iterates over string until it finds other quote and returns its index
if it reached end of string without finding, it throws an error
*/
int	find_closed_quote(t_state *state, int i, char c)
{
	i++;
	while(state->input[i] != c && state->input[i] != 0)
		i++;
	if (state->input[i] == 0) // unclosed quote detected
	{
		// error
		// cleanup
		exit ;
	}
	return (i - 1);
}

/*takes start and end indices of a word and mallocs a t_list variable
with the content of the word 
and adds it to the back of word list in state struct*/
void	create_word(t_state *state, int start, int end)
{
	t_list	*newword;

	// creating new word
	newword = (t_list *)malloc(sizeof(t_list));
	if (newword == NULL)
	{
		exit;
		// cleanup
	}
	newword->content = (char *)malloc((end - start + 2) * sizeof(char));
	if (!newword->content)
	{
		// malloc error
	}
	ft_strlcpy(newword->content, state->input + start, end - start + 1);
	((char *)(newword->content))[end - start + 1] = 0;
	newword->next = NULL;
	ft_lstadd_back(&state->words, newword);
}
