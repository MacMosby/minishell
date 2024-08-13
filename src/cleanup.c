/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wel-safa <wel-safa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 21:34:16 by wel-safa          #+#    #+#             */
/*   Updated: 2024/08/13 21:05:38 by wel-safa         ###   ########.fr       */
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
void	cleanup_shell_exit(t_state *state)
{
	cleanup_shell(state);
	
	// Free state->env
	free_strarr(state->env);
	
	// clear history
	rl_clear_history();
}

void	free_nodes(void *node)
{
	t_node *n;

	n = (t_node *) node;
	ft_lstclear(&(n->words), free);
	free(n);
	// need to free other things in node
}

void	cleanup_shell(t_state *state)
{
	// ask for heredoc input

	//ft_lstclear(&(state->words), free);	// free list of words
	ft_lstclear(&(state->cmds), free_nodes);
	// free hd_content and others ???
	free(state->input); // free input
	state->input = NULL;
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