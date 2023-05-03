/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaisne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/20 13:46:47 by gclement          #+#    #+#             */
/*   Updated: 2023/05/03 10:43:46 by jlaisne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	switch_type(const char c, va_list arg)
{
	if (c == 'c')
	{
		ft_putchar_fd(va_arg(arg, int), 2);
		return (1);
	}
	else if (c == 's')
		return (ft_putstr_and_count(va_arg(arg, char *), 2));
	else if (c == '%')
		return (ft_putchar_fd('%', 1), 2);
	else if (c == 'd')
		return (ft_putnbr_and_count(va_arg(arg, int), 2));
	else if (c == 'u')
		return (ft_put_unsigned_int(va_arg(arg, unsigned int), 2));
	else if (c == 'x')
		return (ft_putnbr_base_and_count(arg, 'x'));
	else if (c == 'X')
		return (ft_putnbr_base_and_count(arg, 'X'));
	else if (c == 'i')
		return (ft_putnbr_and_count(va_arg(arg, int), 2));
	else if (c == 'p')
		return (ft_putnbr_base_and_count(arg, 'p'));
	else if (c != '\0')
		return (ft_putchar_fd(c, 1), 2);
	return (0);
}

int	ft_printf(const char *format, ...)
{
	size_t	i;
	size_t	count;
	va_list	parameters;

	va_start(parameters, format);
	i = 0;
	count = 0;
	if (write(1, 0, 0) != 0)
		return (-1);
	while (i < ft_strlen(format))
	{
		if (format[i] != '%')
		{
			ft_putchar_fd(format[i], 2);
			i++;
			count++;
		}
		else
		{
			i++;
			count += switch_type(format[i], parameters);
			i++;
		}
	}
	return (va_end(parameters), count);
}
