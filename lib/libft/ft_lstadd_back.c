/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wel-safa <wel-safa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 17:52:46 by wel-safa          #+#    #+#             */
/*   Updated: 2023/05/17 20:59:50 by wel-safa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*node;

	if (!(*lst) && new)
	{
		*lst = new;
		return ;
	}
	if (!new || !(*lst))
		return ;
	node = *lst;
	while (node->next)
		node = node->next;
	node->next = new;
	if (!(new->next))
		new->next = NULL;
}
