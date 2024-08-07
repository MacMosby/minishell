/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nodes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wel-safa <wel-safa@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 15:19:55 by wel-safa          #+#    #+#             */
/*   Updated: 2024/08/07 19:27:55 by wel-safa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	create_node(t_state *state, int pipe)
{
	t_node	*node;
	t_list	*cmd;
	t_list	*word;

	cmd = (t_list *) malloc(sizeof(t_list));
	if (cmd == NULL)
	{
		cleanup_shell_exit(state);
		exit(1);
	}
	cmd->next = NULL;
	node = (t_node *) malloc(sizeof(t_node));
	if (node == NULL)
	{
		cleanup_shell_exit(state);
		exit(1); // malloc error
	}
	// should I initialize something here for node?
	node->words = state->words;
	word = node->words;
	if (pipe) // MAYBE THERE IS A BETTER WAY TO DO THIS???
	{
		while (word) // delete pipe from list of words
		{
			if (word->next->next == NULL)
			{
				ft_lstdelone(word->next, free);
				word->next = NULL;
				break;
			}
			word = word->next;
		}
	}
	cmd->content = (void *) node;
	ft_lstadd_back(&(state->cmds), cmd);
}

/*takes state and splits word list into multiple lists per cmd
creates cmd struct and sets state->words to null*/
void	nodes(t_state *state)
{
	t_list	*word;
	t_list	*nextword;

	word = state->words;
	while (word)
	{
		if (ft_strncmp((char *) word->content, "|", 1) == 0)
		{
			nextword = word->next; // save next word after pipe
			word->next = NULL; // end list to be cut including pipe
			create_node(state, 1);
			state->words = nextword;
			word = state->words;
		}
		else if (word->next == NULL)
		{
			create_node(state, 0);
			word = word->next;
		}
		else
			word = word->next;
	}
	state->words = NULL;
}