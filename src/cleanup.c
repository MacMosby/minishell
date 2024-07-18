/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wel-safa <wel-safa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 21:34:16 by wel-safa          #+#    #+#             */
/*   Updated: 2024/07/18 22:24:48 by wel-safa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Cleans up shell on exit
1- frees the environment variables
*/
void	cleanup_shell(t_state *state)
{
	// Free state->env
	free_strarr(state->env);
	
	// clear history
	rl_clear_history();

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