/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wel-safa <wel-safa@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 19:26:09 by wel-safa          #+#    #+#             */
/*   Updated: 2024/07/31 23:22:18 by wel-safa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* takes two word */
void	substr_words(char **first, char **second, char *word, int i, int j)
{
	int	len;

	len = ft_strlen(word);
	*first = ft_substr(word, 0, i);
	*second = ft_substr(word, j + 1, len);
}

/* takes a string: word, cuts out the part from i to j 
and replaces it with another string: rep */
char	*strreplace(char **word, char *rep, int i, int j)
{
	char	*first;
	char	*second;
	char	*tmp;
	char	*res;

	substr_words(&first, &second, *word, i, j);
	if (!rep)
	{
		res = ft_strjoin(first, second);
		free(first);
		free(second);
		free(*word);
		return (res);
	}
	tmp = ft_strjoin(first, rep);
	res = ft_strjoin(tmp, second);
	free(first);
	free(second);
	free(tmp);
	free(*word);
	return (res);
}

void	expand(t_state *state, char **word)
{
	int		j;
	char	*var;
	int		len;
	char	*rep;

	j = state->i + 1;
	var = NULL;
	while((*word)[j])
	{
		if ((*word)[j] == 0 || (*word)[j] == ' ' || (*word)[j] == '\"')
			break ; // end of var and j is index after var
		j++;
	}
	len = j - state->i - 1; // length of variable name
	if (len > 0)
	{
		var = (char *)malloc((len + 1) * sizeof(char));
		// copy var from word.
		ft_memcpy(var, (*word) + state->i + 1, len);
		var[len] = '\0';
		rep = find_var_value(state, var);
		if (!rep)
			rep = ""; // handle when var is not found
		*word = strreplace(word, rep, state->i, state->i + len);
		// index change to after replacement - 1, it will iterate to after.
		state->i += ft_strlen(rep) - 1;
		free(var);
	}
}

void	toexpand(t_state *state, char **word)
{
	int sq_flag;
	int dq_flag;

	sq_flag = 0;
	dq_flag = 0;

	state->i = 0;
	while ((*word)[state->i])
	{
		if ((*word)[state->i] == '\'' && !dq_flag)
			sq_flag = !sq_flag;
		else if ((*word)[state->i] == '\"' && !sq_flag)
			dq_flag = !dq_flag;
		else if ((*word)[state->i] == '$')
		{
			if (!sq_flag && !dq_flag && (*word)[state->i + 1] != 0)
				// not inside any quotes
				// find variable to expand
				// Variable cuts off at quotes, spaces or end of word.
				// if quote is right after $ sign there will be no var
				// and nothing to expand, just remove $ sign
				expand(state, word);
			else if (dq_flag && (*word)[state->i + 1] != ' ' && (*word)[state->i + 1] != '\"')
				// inside double quotes AND there is a VAR assigned after $
				// for example "hello $ " or "hello $", 
				//will be ignored and kept in the wording
				expand(state, word);
		}
		(state->i)++;
	}
}

void	expansion(t_state *state)
{
	printf("\nexpansion...\n\n");
	t_list	*word;

	word = state->words;
	while(word)
	{
		toexpand(state, (char **) &(word->content));
		word = word->next;
	}
}
