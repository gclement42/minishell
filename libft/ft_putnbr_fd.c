/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gclement <gclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 09:29:26 by gclement          #+#    #+#             */
/*   Updated: 2022/11/12 09:37:28 by gclement         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	long int	lnb;

	lnb = n;
	if (lnb < 0)
	{
		lnb *= -1;
		ft_putchar_fd('-', fd);
	}
	if (lnb > 9)
	{
		ft_putnbr_fd(lnb / 10, fd);
	}
	ft_putchar_fd(lnb % 10 + '0', fd);
}
