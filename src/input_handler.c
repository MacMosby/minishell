/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wel-safa <wel-safa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 22:19:22 by wel-safa          #+#    #+#             */
/*   Updated: 2024/07/18 23:33:07 by wel-safa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	carrot(t_state *state, int i)
{
	char	c;
	int		end;

	c = state->input[i];
	end = i;
	while (state->input[end] == c)
		end++;
	if (end - i > 2)
	{
		// more than three carrots
		// error, handle exit and cleanup
		exit (1);
	}
	else if (end - i == 2)
		return (i + 1); // two carrots
	return (i); // only one carrot
}

void	input_handler(t_state *state)
{
	int		i;
	char	*word;
	int		start;
	int		end;

	start = 0;
	end = 0;
	if (ft_strlen(state->input) == 0)
		// handle exit;
		exit;
	word = NULL;
	while (state->input[i])
	{
		start = i;
		if (state->input[i] == ' ')
			i++;
		else if (state->input[i] == '<' || state->input[i] == '>')
		{
			end = carrot(state, i);
			i = end + 1;
		}
		
	}
}

