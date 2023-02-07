/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gclement <gclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 10:44:42 by gclement          #+#    #+#             */
/*   Updated: 2022/11/16 14:49:53 by gclement         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_lnb(long lnb, int *temp, int n)
{
	int		i;

	i = 0;
	*temp = n;
	if (lnb < 0)
		i++;
	while (lnb > 0)
	{
		lnb = lnb / 10;
		i++;
	}
	i++;
	return (i);
}

char	*ft_itoa(int n)
{
	int		i;
	char	*str;
	int		temp;
	long	ln;	

	ln = n;
	if (ln < 0)
		ln *= -1;
	i = count_lnb(ln, &temp, n);
	str = malloc((i + 1) * sizeof(char));
	if (!str)
		return (NULL);
	if (temp > 0)
		i--;
	str[i--] = '\0';
	while (i > 0)
	{
		str[i] = ln % 10 + '0';
		ln = ln / 10;
		i--;
	}
	str[i] = ln + '0';
	if (temp < 0)
		str[0] = '-';
	return (str);
}
