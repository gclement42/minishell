/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base_and_count.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaisne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/20 15:11:35 by gclement          #+#    #+#             */
/*   Updated: 2023/04/19 10:44:58 by jlaisne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	base_is_valid(char *base)
{
	int	i;
	int	j;

	i = 0;
	while (base[i])
	{
		j = 1;
		if (base[i] == '+' || base[i] == '-')
			return (0);
		while (base[i + j] != '\0')
		{
			if (base[i] == base[i + j])
				return (0);
			j++;
		}
		i++;
	}
	if (i <= 1)
		return (0);
	return (i);
}

static int	ft_putnbr_base(unsigned int nbr, char *base, int *i)
{
	unsigned long		lnbr;
	int					base_l;

	base_l = base_is_valid(base);
	lnbr = nbr;
	if (base_l != 0)
	{
		if (lnbr <= 0)
		{
			*i += 1;
			ft_putnbr_base(lnbr / base_l, base, i);
			ft_putchar_fd(base[lnbr % base_l], 1);
		}
		if (lnbr > 0)
		{
			*i += 1;
			ft_putnbr_base(lnbr / base_l, base, i);
			ft_putchar_fd(base[lnbr % base_l], 1);
		}
	}
	return (*i);
}

static int	ft_putnbr_base_long(unsigned long nbr, char *base, int *i)
{
	unsigned long	lnbr;
	unsigned long	base_l;

	base_l = base_is_valid(base);
	lnbr = nbr;
	if (base_l != 0)
	{
		if (lnbr <= 0)
		{
			*i += 1;
			ft_putnbr_base_long(lnbr / base_l, base, i);
			ft_putchar_fd(base[lnbr % base_l], 1);
		}
		if (lnbr > 0)
		{
			*i += 1;
			ft_putnbr_base_long(lnbr / base_l, base, i);
			ft_putchar_fd(base[lnbr % base_l], 1);
		}
	}
	return (*i);
}

int	ft_putnbr_base_and_count(va_list args, int type)
{
	int				i;
	long int		arg;

	i = 0;
	if ((type == 'X') | (type == 'x'))
		arg = va_arg(args, unsigned int);
	else
		arg = va_arg(args, unsigned long);
	if (arg == 0 && ((type == 'x') | (type == 'X')))
		return (ft_putchar_fd('0', 1), 1);
	if (type == 'x')
		return (ft_putnbr_base(arg, "0123456789abcdef", &i), i);
	else if (type == 'X')
		return (ft_putnbr_base(arg, "0123456789ABCDEF", &i), i);
	else if (type == 'p')
	{
		ft_putstr_fd("0x", 1);
		if (arg == 0)
		{
			i++;
			ft_putchar_fd('0', 1);
		}
		return (ft_putnbr_base_long(arg, "0123456789abcdef", &i), i += 2);
	}
	return (i);
}
