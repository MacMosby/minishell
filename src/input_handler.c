/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wel-safa <wel-safa@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 22:19:22 by wel-safa          #+#    #+#             */
/*   Updated: 2024/08/21 21:55:10 by wel-safa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_cmds(t_state *state)
{
	// for testing print list of commands
	t_list *cmd;
	cmd = state->cmds;
	int j = 1;
	while (cmd)
	{
		t_node * node;
		node = (t_node *) cmd->content;
		printf("CMD %i:\n", j);
		printf("\nword list:\n");
		print_list(node->words);
		printf("\ncmd and cmd flag:\n");
		ft_printf("%s\n", node->cmd);
		printf("%i", node->cmd_flag);
		printf("\nargs:\n");
		print_env(node->args);
		printf("\nfd_in: %i\n", node->fd_in);
		printf("fd_out: %i\n", node->fd_out);
		ft_printf("hd_content: %s\n", node->hd_content);
		printf("err_flag: %i\n", node->err_flag);
		j++;
		cmd = cmd->next;
	}
}

void	input_handler(t_state *state)
{
	int		i;

	if (!state || !state->input) // Ensure state and input are valid
        return ;
	i = 0;
	if (ft_strlen(state->input) == 0)
	{
		// check again
		cleanup_shell_exit(state);
		exit(1);
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
		{
			get_heredoc_input(NULL, state->words);
			return ;
		}
	}
	// split into multiple lists per command
	nodes(state);
	
	heredoc_in(state);
	
	//print_cmds(state);
	redirections(state);
	
	//printf("\n|||||AFTER REDIRECTIONS||||\n");
	//print_cmds(state);
	
	expansion(state);
	
	//printf("\n|||||AFTER EXPANSIONS||||\n");
	//print_cmds(state);
	
	splitting(state);
	
	//printf("\n|||||AFTER SPLITTING||||\n");
	//print_cmds(state);
	
	quotes(state);
	
	//printf("\n|||||AFTER REMOVING QUOTES||||\n");
	//print_cmds(state);
	
	cmd_loop(state);

	//printf("\n|||||AFTER handling cmds||||\n");
	//print_cmds(state);
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
	if (c == '>' || c == '<' || c == '|' || c == 0)
	{
		return (-1);
		// syntax error does not execute
		// syntax error, exit, cleanup
		// do I create or open files before this error? NO
		// do I check cmd validity before this error? NO
		// EOF? YES IF IT COMES BEFORE!!!!!
	}
	end = find_word_end(state, start); // find end index of filename or delim
	if (end < 0 || end < start)
		return (-1); // unclosed quote or no word found
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
	{	// $?
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
	int j;

	j = i + 1;
	while (state->input[j] == ' ')
		j++;
	if (state->words == NULL)
	{
		// starts with pipe
		printf("bash: syntax error near unexpected token `|'\n");
		// $?
		//2: command not found
		return (-1); // and cleanup
	}
	else if (state->input[j] == 0) // ends with pipe
		return (-1); // syntax error
	else if (state->input[j] == '|') // double pipe
		return(-1); // syntax error
	create_word(state, i, i);
	return (j); // start of new word
}
