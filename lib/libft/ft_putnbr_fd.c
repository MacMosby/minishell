/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wel-safa <wel-safa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 16:22:01 by wel-safa          #+#    #+#             */
/*   Updated: 2023/05/15 16:55:09 by wel-safa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	long int	ln;
	char		c;

	ln = n;
	if (fd < 0)
		return ;
	if (ln < 0)
	{
		ln *= -1;
		write(fd, "-", 1);
	}
	if (ln / 10 > 0)
	{
		ft_putnbr_fd(ln / 10, fd);
		ft_putnbr_fd(ln % 10, fd);
	}
	if (ln / 10 == 0)
	{
		c = ln + '0';
		write(fd, &c, 1);
	}
}
/*
int	main(void)
{
	ft_putnbr_fd(42, 1);
}
*/