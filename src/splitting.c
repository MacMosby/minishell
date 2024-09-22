/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splitting.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wel-safa <wel-safa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 23:39:02 by wel-safa          #+#    #+#             */
/*   Updated: 2024/09/22 22:24:37 by wel-safa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*takes start index s and end index e and
string pointer word and t_list double pointer newwordlist
it creates new word from index s to e of char **word
and adds it to newwordlist
first if statement is true if space is at beg or end of word*/
int	split_words_create(int s, int e, char **word, t_list **newwordlist)
{
	t_list	*newword;

	if (s > ((int)ft_strlen(*word) - 1) || e < 0)
		return (0);
	newword = (t_list *)malloc(sizeof(t_list));
	if (!newword)
		return (-1);
	newword->content = (char *)malloc((e - s + 2) * sizeof(char));
	if (!newword->content)
		return (-1);
	ft_strlcpy(newword->content, *word + s, e - s + 2);
	newword->next = NULL;
	ft_lstadd_back(newwordlist, newword);
	return (0);
}

/*takes string pointer word and t_list double pointer for newwordlist nwl
if it finds a space not inside quotes, it splits word at that index 
into two words
adds them to list newwordlist
if space is at beginning or end of word,
it will return a list of one word removing the space
*/
void	split_words(t_state *state, char **word, t_list **nwl)
{
	int		sq_flag;
	int		dq_flag;
	int		i;

	sq_flag = 0;
	dq_flag = 0;
	i = 0;
	while ((*word)[i])
	{
		if ((*word)[i] == '\'' && !dq_flag)
			sq_flag = !sq_flag;
		else if ((*word)[i] == '\"' && !sq_flag)
			dq_flag = !dq_flag;
		if ((*word)[i] == ' ' && !sq_flag && !dq_flag)
		{
			if (split_words_create(0, i - 1, word, nwl) < 0)
				error_exit(state);
			if (split_words_create(i + 1, 
					((int)ft_strlen(*word)) - 1, word, nwl) < 0)
				error_exit(state);
			break ;
		}
		i++;
	}
}

void	insert_nwl(t_list *bef, t_list *aft, t_list *nwl, t_node *cmd_content)
{
	if (bef)
		bef->next = nwl;
	else
		cmd_content->words = nwl;
	if (nwl->next)
		nwl->next->next = aft;
	else
		nwl->next = aft;
}

/*splitting words after expansion: it iterates over list of words
if it finds a word with space not inside quotes, it splits into two words,
and inserts new list of two words
in place of the one word in the t_list words in t_node cmd_content,
it then loops again on second replaced word*/
void	splitting_cmd_words(t_state *state, t_node *cmd_content)
{
	t_list	*word;
	t_list	*before;
	t_list	*after;
	t_list	*newwordlist;

	word = cmd_content->words;
	before = NULL;
	while (word)
	{
		after = word->next;
		newwordlist = NULL;
		split_words(state, (char **) &(word->content), &newwordlist);
		if (newwordlist)
		{
			insert_nwl(before, after, newwordlist, cmd_content);
			ft_lstdelone(word, free);
			word = newwordlist;
		}
		else
		{
			before = word;
			word = after;
		}
	}
}

/*iterates over list of commans in t_state variable state and calls
splitting_cmd_words on each command node*/
void	splitting(t_state *state)
{
	t_list	*cmd;

	cmd = state->cmds;
	while (cmd)
	{
		splitting_cmd_words(state, (t_node *)(cmd->content));
		cmd = cmd->next;
	}
}
