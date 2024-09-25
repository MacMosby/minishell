/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_handler_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wel-safa <wel-safa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 20:54:36 by wel-safa          #+#    #+#             */
/*   Updated: 2024/09/25 21:14:29 by wel-safa         ###   ########.fr       */
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
		return (3);
	else if (end - start == 2)
		return (2);
	return (1);
}

/*takes index of start of word i
and finds the end i.e. (|, , >, <) or end of string
returns end of word character index*/
int	find_word_end(t_state *state, int i)
{
	char	c;

	while (state->input[i])
	{
		c = state->input[i];
		while (c == '\'' || c == '\"')
		{
			i = find_closed_quote(state, i) + 1;
			if (i < 0)
				return (-1);
			c = state->input[i];
		}
		if (ft_isspace(c) || c == '|' || c == '>' || c == '<' || c == 0)
			return (i - 1);
		i++;
	}
	return (i - 1);
}

/*takes index i of start of quotes
and assigns char c to the quote whether double or single
iterates over string until it finds other quote and returns its index
if it reached end of string without finding, it throws an error
*/
int	find_closed_quote(t_state *state, int i)
{
	char	c;

	c = state->input[i];
	i++;
	while (state->input[i] != 0)
	{
		if (state->input[i] == c)
			return (i);
		i++;
	}
	write(2, "syntax error unclosed quotes\n", 29);
	return (-2);
}

/*takes start and end indices of a word and mallocs a t_list variable
with the content of the word
and adds it to the back of word list in state struct*/
void	create_word(t_state *state, int start, int end)
{
	t_list	*newword;

	newword = (t_list *)malloc(sizeof(t_list));
	if (!newword)
		error_exit(state);
	newword->content = (char *)malloc((end - start + 2) * sizeof(char));
	if (!newword->content)
		error_exit(state);
	ft_strlcpy(newword->content, state->input + start, end - start + 2);
	newword->next = NULL;
	ft_lstadd_back(&state->words, newword);
}
