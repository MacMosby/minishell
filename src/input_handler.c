/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wel-safa <wel-safa@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 22:19:22 by wel-safa          #+#    #+#             */
/*   Updated: 2024/07/31 22:32:44 by wel-safa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// redirections first from left to right redirection error errflag
// then check function (cmd not found is the errflag)

void	input_handler(t_state *state)
{
	int		i;

	i = 0;
	if (ft_strlen(state->input) == 0)
		// handle exit;
		exit (1);
	while (state->input[i])
	{
		if (state->input[i] == ' ')
			i++;
		else if (state->input[i] == '<' || state->input[i] == '>')
			i = carroting(state, i);
		else if (state->input[i] == '|')
			i = piping(state, i);
		else
			// command or argument
			i = wording(state, i);
	}
	expansion(state);
	//print_list(state->words);
	splitting(state);
	//remove_quotes(state);
}

/*invoked when carrot is encounter in string input in t_state struct state
it creates a word for the carrots (whether single or double)
then iterates over spaces to find the filename after the carrot
if the filename starts with | or > or <, it throws a syntax error
otherwise, it uses find_word_end function to create the filename word
it returns the index of the character after*/
int	carroting(t_state *state, int start)
{
	int 	carrots;
	char	c;
	int		end;

	carrots = carrotcount(state, start);
	create_word(state, start, start + carrots - 1); // create carrot as word
	c = state->input[start];
	if (c == '<' && carrots == 2)
	{
		// << heredoc
		// end after heredoc 
		end = start + 2;
	}
	else // < or > or >>
	{
		start = start + carrots; // start on next character after carrot
		while (state->input[start] == ' ') // iterate over spaces
			start++;
		c = state->input[start];
		if (c == '>' || c == '<' || c == '|')
		{
			exit (1);
			// syntax error, exit, cleanup
			// do I create or open files before this error? NO
			// do I check cmd validity before this error? NO
			// EOF? NO
		}
		end = find_word_end(state, start); // find end of filename
		create_word(state, start, end); // create filename as word 
	}
	return (end + 1); // return index of next character
}

/*takes start of word and finds end and creates word
returns index after word*/
int wording(t_state *state, int start)
{
	int	end;

	end = find_word_end(state, start);
	create_word(state, start, end);
	return (end + 1);
}

/*takes index x of the 'pipe' character in input string
iterates over spaces and throws syntax error if string starts with pipe
ends with pipe, or a double pipe is found
Otherwise it creates a word of the pipe character
returns start of next word
*/
int	piping(t_state *state, int i)
{
	int j;

	j = i + 1;
	while (state->input[j] == ' ')
		j++;
	if (state->words == NULL) // starts with pipe
		// bash: syntax error near unexpected token `|' 
		// $?
		//2: command not found
		exit (1); // and cleanup
	else if (state->input[j] == 0) // ends with pipe
		exit (1); // syntax error
	else if (state->input[j] == '|') // double pipe
		exit(1); // syntax error
	create_word(state, i, i);
	return (j); // start of new word
}
