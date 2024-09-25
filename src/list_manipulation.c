/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_manipulation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wel-safa <wel-safa@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 20:09:36 by mrodenbu          #+#    #+#             */
/*   Updated: 2024/09/25 09:14:05 by wel-safa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define HD "<<"
#define APP ">>"
#define IN "<"
#define OUT ">"

/* takes a node as an arguments, iterates over the t_list words element
of the nodes and creates an array out of the words and puts this into
the node as char **args to be used in execve */
void	wordlist_to_cmdarr(t_state *state, t_node *cmd)
{
	int		count;
	t_list	*curr;
	char	**arr;
	int		i;

	count = 0;
	if (cmd)
		count = ft_lstsize(cmd->words);
	if (!count)
		return ;
	arr = (char **)malloc((count + 1) * sizeof(char *));
	if (!arr)
		error_exit(state);
	curr = cmd->words;
	i = 0;
	while (i < count)
	{
		arr[i] = ft_strdup(curr->content);
		i++;
		curr = curr->next;
	}
	arr[i] = NULL;
	cmd->args = arr;
}

void	free_carrots_plus_one(t_list *curr)
{
	free(curr->next->content);
	curr->next->next = NULL;
	free(curr->next);
	free(curr->content);
	curr->next = NULL;
	free(curr);
}

/* takes a list of word as an argument and deletes all words that
are redirection carrots and the following arguments which are the
filenames/heredoc delimiteres to clean the list so that the list
contains the command and the command arguments only */
void	delete_redirections(t_list **words, t_list *before, t_list *new)
{
	t_list	*curr;

	curr = *words;
	while (curr)
	{
		if (found_carrot(curr->content))
		{
			if (curr->next->next)
				new = curr->next->next;
			else
				new = NULL;
			if (!before)
				*words = new;
			else
				before->next = new;
			free_carrots_plus_one(curr);
			curr = new;
		}
		else
		{
			before = curr;
			curr = curr->next;
		}
	}
}
