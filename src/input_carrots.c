/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_carrots.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wel-safa <wel-safa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 19:15:17 by wel-safa          #+#    #+#             */
/*   Updated: 2024/09/25 21:12:07 by wel-safa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	carroting_errors(t_state *state, char c, int start)
{
	if (c == 0)
		write(2, "minishell: syntax error near \
unexpected token `newline'\n", 56);
	else if (c == '>')
	{
		if (state->input[start + 1] == '>')
			write(2, "minishell: syntax error near unexpected token `>>'\n", 51);
		else
			write(2, "minishell: syntax error near unexpected token `>'\n", 50);
	}
	else if (c == '<')
	{
		if (state->input[start + 1] == '<')
			write(2, "minishell: syntax error near unexpected token `<<'\n", 51);
		else
			write(2, "minishell: syntax error near unexpected token `<'\n", 50);
	}
	else if (c == '|')
		write(2, "minishell: syntax error near unexpected token `|'\n", 50);
	state->exit_status = 2;
	return (-1);
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
	c = state->input[start];
	if (carrots >= 3)
		return (carroting_errors(state, c, start + 2));
	create_word(state, start, start + carrots - 1);
	start = start + carrots;
	while (ft_isspace(state->input[start]))
		start++;
	c = state->input[start];
	if (c == '>' || c == '<' || c == '|' || c == 0)
		return (carroting_errors(state, c, start));
	end = find_word_end(state, start);
	if (end < 0 || end < start)
		return (-1);
	create_word(state, start, end);
	return (end + 1);
}
