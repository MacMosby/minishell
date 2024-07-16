/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wel-safa <wel-safa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 14:05:21 by wel-safa          #+#    #+#             */
/*   Updated: 2024/01/28 17:21:20 by wel-safa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printstr(char *s)
{
	if (s == NULL)
	{
		write(1, "(null)", 6);
		return (6);
	}
	if (ft_strlen(s) == 0)
		return (0);
	write(1, s, ft_strlen(s));
	return (ft_strlen(s));
}

int	ft_putptr(void *ptr)
{
	unsigned long long	address;

	address = (unsigned long long)ptr;
	if (address == 0)
	{
		write(1, "(nil)", 5);
		return (5);
	}
	ft_putchar('0');
	ft_putchar('x');
	return (ft_putnbr_base(address, "0123456789abcdef", 2));
}

int	ft_process_string(const char *str, va_list args, size_t i, int count)
{
	while (++i < ft_strlen(str))
	{
		if (str[i] == '%' && str[++i])
		{
			if (str[i] == '%')
				count += ft_putchar('%');
			else if (str[i] == 'c')
				count += ft_putchar(va_arg(args, int));
			else if (str[i] == 's')
				count += ft_printstr(va_arg(args, char *));
			else if (str[i] == 'p')
				count += ft_putptr(va_arg(args, void *));
			else if (str[i] == 'd' || str[i] == 'i')
				count += ft_putnbr_count(va_arg(args, int), 1, 0);
			else if (str[i] == 'u')
				count += ft_putunsignednbr_fd(va_arg(args, unsigned int), 1, 0);
			else if (str[i] == 'x' || str[i] == 'X')
				count += ft_putnbr_case(str[i], va_arg(args, unsigned int));
		}
		else
			count += ft_putchar(str[i]);
	}
	return (count);
}

int	ft_printf(const char *str, ...)
{
	int		count;
	va_list	args;

	if (str == 0)
		return (-1);
	va_start(args, str);
	count = ft_process_string(str, args, -1, 0);
	va_end(args);
	return (count);
}
/*
int	ft_printf(const char *str, ...)
{
	size_t	i;
	int		count;
	va_list	args;

	i = -1;
	count = 0;
	if (str == 0)
		return (-1);
	va_start(args, str);
	while (++i < ft_strlen(str))
	{
		if (str[i] == '%' && str[++i])
		{
			if (str[i] == '%')
				count += ft_putchar('%');
			else if (str[i] == 'c')
				count += ft_putchar(va_arg(args, int));
			else if (str[i] == 's')
				count += ft_printstr(va_arg(args, char *));
			else if (str[i] == 'p')
				count += ft_putptr(va_arg(args, void *));
			else if (str[i] == 'd' || str[i] == 'i')
				count += ft_putnbr_fd(va_arg(args, int), 1, 0);
			else if (str[i] == 'u')
				count += ft_putunsignednbr_fd(va_arg(args, unsigned int), 1, 0);
			else if (str[i] == 'x')
				count += ft_putnbr_base(va_arg(args, unsigned int), "0123456789abcdef", 0);
			else if (str[i] == 'X')
				count += ft_putnbr_base(va_arg(args, unsigned int), "0123456789ABCDEF", 0);
		}
		else
			count += ft_putchar(str[i]);
	}
	return (count);
}
*/
/*int	main(void)
{
	char c = 'Z';
	char *p = &c;
	int d = -2147483648;
	int i = 2147483647;
	unsigned int u = 4294967295;
	unsigned int x = 42949645;
	unsigned int X = 42949645;

	//printf("printf: %% %c %p %s %d %i %u %x %X\n",
	//c, p, "String", d, i, u, x, X);
	//ft_printf("fprint: %% %c %p %s %d %i %u %x %X\n",
	//c, p, "String", d, i, u, x, X);
	//printf("ft_putnbr_base: ");
	int a = 0;
	int b = 0;
	a = printf("printf= |%s|\n", "");
	b = ft_printf("fprint= |%s|\n", "");
	printf("%i %i \n", a, b);

	a = printf("printf= |%c|\n", '0');
	b = ft_printf("fprint= |%c|\n", '0');
	printf("%i %i \n", a, b);
	
	a = printf("printf= NULL %s NULL \n", (char *)NULL);
	b = ft_printf("fprint= NULL %s NULL \n", NULL);
	printf("%i %i \n", a, b);

	a = ft_printf(" %p %p ", 0, 0);
	printf("%i\n", a);

	printf("%i\n", printf(""));
	printf("%i\n", ft_printf(""));
}*/
