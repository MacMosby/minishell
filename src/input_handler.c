/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wel-safa <wel-safa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 22:19:22 by wel-safa          #+#    #+#             */
/*   Updated: 2024/09/15 21:20:54 by wel-safa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	input_handler(t_state *state)
{
	int		i;

	if (!state)
		return (-1);
	if (!state->input)
		return (-1);
	if (ft_strlen(state->input) == 0)
		return (-1);
	i = 0;
	while (state->input[i])
	{
		if (state->input[i] == ' ')
			i++;
		else if (state->input[i] == '<' || state->input[i] == '>')
			i = carroting(state, i);
		else if (state->input[i] == '|')
			i = piping(state, i);
		else
			i = wording(state, i);
		if (i < 0)
		{
			get_heredoc_input(state, NULL, state->words);
			return (-1);
		}
	}
	nodes(state);
	heredoc_in(state);
	if (g_signal)
		return (0);
	redirections(state);
	expansion(state);
	splitting(state);
	quotes(state);
	cmd_loop(state);
	return (0);
}

/*invoked when carrot is encountered in string input in t_state struct state
it creates a word for the carrots (whether single or double)
then iterates over spaces to find the filename after the carrot
if the filename starts with | or > or <, it throws a syntax error
otherwise, it uses find_word_end function to create the filename word
it returns the index of the character after*/
int	carroting(t_state *state, int start)
{
	int		carrots;
	char	c;
	int		end;

	carrots = carrotcount(state, start);
	if (carrots == 3)
	{
		write(2, " syntax error near unexpected token `>'\n", 40);
		state->exit_status = 2;
		return (-1);
	}
	create_word(state, start, start + carrots - 1);
	c = state->input[start];
	start = start + carrots;
	while (state->input[start] == ' ')
		start++;
	c = state->input[start];
	if (c == '>' || c == '<' || c == '|' || c == 0)
	{
		if (c == 0)
			write(2, " syntax error near unexpected token `newline'\n", 46);
		else if (c == '>')
		{
			if (state->input[start + 1] == '>')
				write(2, " syntax error near unexpected token `>>'\n", 41);
			else
				write(2, " syntax error near unexpected token `>'\n", 40);
		}
		else if (c == '<')
		{
			if (state->input[start + 1] == '<')
				write(2, " syntax error near unexpected token `<<'\n", 41);
			else
				write(2, " syntax error near unexpected token `<'\n", 40);
		}
		else if (c == '|')
			write(2, " syntax error near unexpected token `|'\n", 40);
		state->exit_status = 2;
		return (-1);
	}
	end = find_word_end(state, start);
	if (end < 0 || end < start)
		return (-1); // unclosed quote or no word found
	create_word(state, start, end); // create word or filename or delim as word
	return (end + 1); // return index of next character
}

/*takes start of word and finds end and creates word
returns index after word*/
int	wording(t_state *state, int start)
{
	int	end;

	end = find_word_end(state, start);
	if (end < 0)
	{
		// $?
		return (-1); // unclosed quote
	}
	create_word(state, start, end);
	return (end + 1);
}

/*takes index i of the 'pipe' character in input string
iterates over spaces and throws syntax error if string starts with pipe
ends with pipe, or a double pipe is found
Otherwise it creates a word of the pipe character
returns start of next word
*/
int	piping(t_state *state, int i)
{
	int	j;

	j = i + 1;
	while (state->input[j] == ' ')
		j++;
	if (state->words == NULL)
	{
		// starts with pipe
		write(2, " syntax error near unexpected token `|'\n", 40);
		// $? -> 2
		state->exit_status = 2;
		return (-1); // and cleanup
	}
	else if (state->input[j] == 0) // ends with pipe
	{
		write(2, " syntax error near unexpected token `|'\n", 40);
		state->exit_status = 2;
		return (-1); // syntax error
	}
	else if (state->input[j] == '|') // double pipe
	{
		write(2, " syntax error near unexpected token `|'\n", 40);
		state->exit_status = 2;
		return (-1); // syntax error
	}
	create_word(state, i, i);
	return (j); // start of new word
}
