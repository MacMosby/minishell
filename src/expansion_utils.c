/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wel-safa <wel-safa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 20:23:37 by wel-safa          #+#    #+#             */
/*   Updated: 2024/09/22 21:15:52 by wel-safa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	expand_exit_status(t_state *state, char **word, int i, int j)
{
	char	*rep;

	rep = ft_itoa(state->exit_status);
	*word = strreplace(word, rep, i, j);
	free(rep);
	return (i - 1 + ft_strlen(rep));
}

int	expand_replace(t_state *state, char **word, int len, int i)
{
	char	*var;
	char	*rep;

	var = (char *)malloc((len + 1) * sizeof(char));
	if (!var)
		error_exit(state);
	ft_memcpy(var, (*word) + i + 1, len);
	var[len] = '\0';
	rep = find_var_value(state, var);
	if (!rep)
		rep = "";
	free(var);
	*word = strreplace(word, rep, i, i + len);
	i += ft_strlen(rep) - 1;
	return (i);
}

/*takes t_state struct and string pointer word and index i of the dollar sign
found and hd_flag that signifies if it is a heredoc expansion or not.
It finds variable after $ sign.
if var is found, it searches env for var and replaces $VAR from word 
with its value, otherwise it removes $VAR from word.
if variable is not found, no expansions happen.
except when hd_flag is 0 AND in such cases: $"hello" or $'hello'
where the dollar sign is removed.
it returns index last character (replacement or no replacement)
*/
int	expand(t_state *state, char **word, int i, int hd_flag)
{
	int		j;
	int		len;

	j = i + 1;
	if ((*word)[j] == '?')
		return (expand_exit_status(state, word, i, j));
	if (ft_isdigit((*word)[j]))
	{
		*word = strreplace(word, NULL, i, i + 1);
		return (i - 1);
	}
	while ((*word)[j] && var_letter((*word)[j]))
		j++;
	len = j - i - 1;
	if (len > 0)
		return (expand_replace(state, word, len, i));
	else if (!hd_flag && ((*word)[j] == '\"' || (*word)[j] == '\''))
	{
		*word = strreplace(word, NULL, i, i);
		i -= 1;
	}
	return (i);
}
