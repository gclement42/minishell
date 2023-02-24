/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_and_count.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gclement <gclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 17:15:19 by gclement          #+#    #+#             */
/*   Updated: 2022/12/09 09:58:24 by gclement         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_nbr(int n)
{
	long	ln;
	int		i;

	i = 0;
	ln = n;
	if (ln <= 0)
	{
		i++;
		ln *= -1;
	}
	while (ln > 0)
	{
		ln = ln / 10;
		i++;
	}
	return (i);
}

int	ft_putstr_and_count(char *s, int fd)
{
	if (s == NULL)
	{
		ft_putstr_fd("(null)", 1);
		return (6);
	}
	ft_putstr_fd(s, fd);
	return (ft_strlen(s));
}

int	ft_putnbr_and_count(int n, int fd)
{
	ft_putnbr_fd(n, fd);
	return (count_nbr(n));
}

int	ft_put_unsigned_int(unsigned int nbr, int fd)
{
	long int	lnb;
	int			i;

	i = 0;
	lnb = nbr;
	if (lnb > 9)
		ft_putnbr_fd(lnb / 10, fd);
	ft_putchar_fd(lnb % 10 + '0', fd);
	if (lnb == 0)
		i++;
	while (lnb > 0)
	{
		lnb = lnb / 10;
		i++;
	}
	return (i);
}
