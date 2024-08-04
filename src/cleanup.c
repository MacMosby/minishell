/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wel-safa <wel-safa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 21:34:16 by wel-safa          #+#    #+#             */
/*   Updated: 2024/08/04 17:53:45 by wel-safa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Cleans up shell on exit
1- frees the environment variables
2- clear history
3- clear words list
4- free input
...
....
*/
void	cleanup_shell(t_state *state)
{
	// Free state->env
	free_strarr(state->env);
	
	// clear history
	rl_clear_history();
	
	// free list of words
	ft_lstclear(&(state->words), free);

	// free input
	free(state->input);
}

/*frees an array of strings*/
void	free_strarr(char **strarr)
{
	int i;

	i = 0;
	while(strarr[i] != NULL)
	{
		free(strarr[i]);
		i++;
	}
	free(strarr[i]);
	free(strarr);
}