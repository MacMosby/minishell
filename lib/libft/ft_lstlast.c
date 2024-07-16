/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wel-safa <wel-safa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 16:17:09 by wel-safa          #+#    #+#             */
/*   Updated: 2023/05/17 18:12:17 by wel-safa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}
/*
int	main(void)
{
	t_list *head;
	head = ft_lstnew("Hello");
	ft_lstadd_front(&head, ft_lstnew("You"));
	t_list *lst;
	lst = ft_lstlast(head);
	printf("%s\n", (char *)lst->content);
	return (0);
}*/
