/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wel-safa <wel-safa@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 22:19:22 by wel-safa          #+#    #+#             */
/*   Updated: 2024/08/07 19:23:28 by wel-safa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	input_handler(t_state *state)
{
	int		i;

	if (!state || !state->input) // Ensure state and input are valid
        return;
	i = 0;
	if (ft_strlen(state->input) == 0)
	{
		// check again
		return ;
	}
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
		if (i < 0)
			return ;
	}
	// split into multiple lists per command
	nodes(state);
	
	// for testing print list of commands
	t_list *cmd;
	cmd = state->cmds;
	int j = 0;
	while (cmd)
	{
		t_node * node;
		node = (t_node *) cmd->content;
		printf("list %i:\n", j);
		print_list(node->words);
		j++;
		cmd = cmd->next;
	}
	
	// what errors did we check for so far?
		// Unclosed quotes
		// pipe at beg or end or double pipes
		// more than 2 carrots (prints error then Heredoc)
		// file name starts with pipe or carrots (prints error then Heredoc)
	// heredoc
	//expansion(state);
	//splitting(state);
	//quotes(state);

}

/*invoked when carrot is encountered in string input in t_state struct state
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
	if (carrots == 3)
	{
		printf("minishell: syntax error, 3 or more carrots\n");
		// error status
		return (-1);
	}
	create_word(state, start, start + carrots - 1); // create carrot as word
	c = state->input[start];
	start = start + carrots; // start on next character after carrots
	while (state->input[start] == ' ') // iterate over spaces
		start++;
	c = state->input[start];
	if (c == '>' || c == '<' || c == '|')
	{
		return (-1);
		// syntax error does not execute
		// syntax error, exit, cleanup
		// do I create or open files before this error? NO
		// do I check cmd validity before this error? NO
		// EOF? YES IF IT COMES BEFORE!!!!!
	}
	end = find_word_end(state, start); // find end index of filename or delim
	if (end < 0)
		return (-1); // unclosed quote
	create_word(state, start, end); // create word or filename or delim as word 
	return (end + 1); // return index of next character
}

/*takes start of word and finds end and creates word
returns index after word*/
int wording(t_state *state, int start)
{
	int	end;

	end = find_word_end(state, start);
	if (end < 0)
		return (-1); // unclosed quote
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
	int j;

	j = i + 1;
	while (state->input[j] == ' ')
		j++;
	if (state->words == NULL) 
		// starts with pipe
		// bash: syntax error near unexpected token `|' 
		// $?
		//2: command not found
		return (-1); // and cleanup
	else if (state->input[j] == 0) // ends with pipe
		return (-1); // syntax error
	else if (state->input[j] == '|') // double pipe
		return(-1); // syntax error
	create_word(state, i, i);
	return (j); // start of new word
}
