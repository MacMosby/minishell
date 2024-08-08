/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wel-safa <wel-safa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 19:21:09 by wel-safa          #+#    #+#             */
/*   Updated: 2024/08/08 17:17:17 by wel-safa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	heredoc_in(t_state * state)
{
	t_list *cmd;
	t_node	*cmd_content;

	cmd = state->cmds;
	cmd_content = (t_node *) cmd->content;
	while (cmd)
	{
		getheredocin((t_list *) cmd_content->words);
		cmd = cmd->next;
		cmd_content = cmd->content;
	}
}

void getheredocin(t_list *words) // gets list of words per cmd
/*iterate over list. Once it finds <<, it will prompt the user for input, 
using delim to end the input, and then replace the delimitor content.
free(delim)
assign delim list item->content = new heredoc input
*/