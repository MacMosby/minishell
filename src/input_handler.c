/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wel-safa <wel-safa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 22:19:22 by wel-safa          #+#    #+#             */
/*   Updated: 2024/09/22 19:20:13 by wel-safa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	input_handler(t_state *state)
{
	if (parsing(state, 0) < 0)
		return (-1);
	nodes(state);
	heredoc_in(state);
	if (g_signal)
		return (1);
	redirections(state);
	expansion(state);
	splitting(state);
	quotes(state);
	cmd_loop(state);
	return (0);
}

int	parsing(t_state *state, int i)
{
	if (!state)
		return (-1);
	if (!state->input)
		return (-1);
	if (ft_strlen(state->input) == 0)
		return (-1);
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
			iterate_for_heredoc(state, NULL, state->words);
			return (-1);
		}
	}
	return (0);
}

/*takes start of word and finds end and creates word
returns index after word*/
int	wording(t_state *state, int start)
{
	int	end;

	end = find_word_end(state, start);
	if (end < 0)
	{
		state->exit_status = 2;
		return (-1);
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
		write(2, "minishell: syntax error near unexpected token `|'\n", 50);
		state->exit_status = 2;
		return (-1);
	}
	else if (state->input[j] == 0)
	{
		write(2, "minishell: syntax error near unexpected token `|'\n", 50);
		state->exit_status = 2;
		return (-1);
	}
	else if (state->input[j] == '|')
	{
		write(2, "minishell: syntax error near unexpected token `|'\n", 50);
		state->exit_status = 2;
		return (-1);
	}
	create_word(state, i, i);
	return (j);
}
