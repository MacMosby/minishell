/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_manipulation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wel-safa <wel-safa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 20:09:36 by mrodenbu          #+#    #+#             */
/*   Updated: 2024/09/14 20:08:22 by wel-safa         ###   ########.fr       */
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
void	wordlist_to_cmdarr(t_node *cmd)
{
	int	count;
	t_list	*curr;
	char	**arr;
	int	i;

	count = 0;
	// if (!cmd) -> return
	// if (!cmd->words) -> return

	if (cmd)
		count = ft_lstsize(cmd->words);
	arr = (char **)malloc((count + 1) * sizeof(char *));
	if (!arr)
		// what should happen here ???
		return;
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
	//print_arr(cmd->args);
}

/* takes a list of word as an argument and deletes all words that
are redirection carrots and the following arguments which are the
filenames/heredoc delimiteres to clean the list so that the list
contains the command and the command arguments only */
void	delete_redirections(t_list **words)
{
	t_list	*curr;
	t_list	*before;
	t_list	*new;
	//t_node	cmd;

	//print_list(words);
	before = NULL;
	curr = *words;
	while (curr)
	{
		if (ft_strncmp(curr->content, HD, 2) == 0
			|| ft_strncmp(curr->content, APP, 2) == 0
			|| ft_strncmp(curr->content, IN, 1) == 0
			|| ft_strncmp(curr->content, OUT, 1) == 0)
		{
			//printf("found carrots\n");
			if (!before)
			{
				if (curr->next->next)
				{
					*words = curr->next->next;
					new = curr->next->next;
				}
				else
				{
					*words = NULL;
					new = NULL;
				}
			}
			else
			{
				if (curr->next->next)
				{
					before->next = curr->next->next;
					new = curr->next->next;
				}
				else
				{
					before->next = NULL;
					new = NULL;
				}
			}
			free(curr->content);
			free(curr->next->content);
			curr->next->next = NULL;
			free(curr->next);
			curr->next = NULL;
			free(curr);
			curr = new;
		}
		else
		{
			before = curr;
			curr = curr->next;
		}
	}
	// the 2 commented lines are just to test the function above
	//cmd.words = *words;
	//print_list(words);
	//wordlist_to_cmdarr(&cmd);
}