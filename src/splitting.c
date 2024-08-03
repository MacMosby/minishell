/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splitting.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wel-safa <wel-safa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 23:39:02 by wel-safa          #+#    #+#             */
/*   Updated: 2024/08/03 18:00:56 by wel-safa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	split_words_create(int s, int e, char **word, t_list **newwordlist)
{
	t_list	*newword;

	if (s > ((int)ft_strlen(*word) - 1) || e < 0)
		// happens when space at beginning or end of word
		return ;
	newword = (t_list *)malloc(sizeof(t_list));
	if (newword == NULL)
	{
		// cleanup_shell(state);
		// malloc protection
		exit(1);
	}
	newword->content = (char *)malloc((e - s + 2) * sizeof(char));
	if (newword->content == NULL)
		// malloc protection
		exit(1);
	ft_strlcpy(newword->content, *word + s, e - s + 2);
	newword->next = NULL;
	ft_lstadd_back(newwordlist, newword);
}

void	split_words(char **word, t_list **newwordlist)
{
	int 	sq_flag;
	int		dq_flag;
	int		i;

	sq_flag = 0;
	dq_flag = 0;
	i = 0;
	while((*word)[i])
	{
		if ((*word)[i] == '\'' && !dq_flag)
			sq_flag = !sq_flag;
		else if ((*word)[i] == '\"' && !sq_flag)
			dq_flag = !dq_flag;
		if ((*word)[i] == ' ' && !sq_flag && !dq_flag)
		{
			split_words_create(0, i - 1, word, newwordlist);
			split_words_create(i + 1, ((int)ft_strlen(*word)) - 1, word, newwordlist);
			break;
		}
		i++;
	}
}

void	splitting(t_state *state)
{	
	//printf("\nsplitting...\n");
	t_list *word;
	t_list	*before;
	t_list	*after;
	t_list	*newwordlist;


	word = state->words;
	newwordlist = NULL;
	before = NULL;
	
	while (word)
	{
		after = word->next;
		newwordlist = NULL;
		split_words((char **) &(word->content), &newwordlist);
		if (newwordlist)
		{
			if (before)
				before->next = newwordlist;
			else
				state->words = newwordlist;
			if (newwordlist->next)
				newwordlist->next->next = after;
			else
				newwordlist->next = after;
			ft_lstdelone(word, free);
			word = newwordlist->next;
		}
		else
		{
			before = word;
			word = after;
		}
	}
}
