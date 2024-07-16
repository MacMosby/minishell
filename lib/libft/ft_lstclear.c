/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wel-safa <wel-safa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 19:26:07 by wel-safa          #+#    #+#             */
/*   Updated: 2023/05/17 19:53:28 by wel-safa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*Deletes and frees the given node and every
successor of that node, using the function ’del’
and free(3).
Finally, the pointer to the list must be set to
NULL.*/

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*temp;
	t_list	*node;

	if (!lst || !del)
		return ;
	node = *lst;
	while (node)
	{
		temp = node;
		del(temp->content);
		node = temp->next;
		free(temp);
	}
	*lst = NULL;
}
