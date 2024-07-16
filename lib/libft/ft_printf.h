/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wel-safa <wel-safa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 14:11:58 by wel-safa          #+#    #+#             */
/*   Updated: 2024/01/28 19:34:36 by wel-safa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdarg.h>
# include <stdlib.h>
# include <string.h>
# include <bsd/string.h>
# include <stdio.h>

int		ft_printf(const char *str, ...);
size_t	ft_strlen(const char *s);
int		ft_strlen_valid(char *str);
int		ft_printstr(char *s);
int		ft_putchar(char c);
int		ft_putnbr_count(int n, int fd, int count);
int		ft_putunsignednbr_fd(unsigned int n, int fd, int count);
int		ft_putnbr_base(unsigned long long nb, char *base, int count);
int		ft_putnbr_case(char c, unsigned int nbr);
int		ft_putptr(void *ptr);
int		ft_process_string(const char *str, va_list args, size_t i, int count);

#endif
