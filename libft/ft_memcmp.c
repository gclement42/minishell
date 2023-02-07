/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gclement <gclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 12:51:24 by gclement          #+#    #+#             */
/*   Updated: 2022/11/16 15:01:14 by gclement         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t					i;
	unsigned char			*str1;
	unsigned char			*str2;

	str1 = ((unsigned char *)s1);
	str2 = ((unsigned char *)s2);
	i = 0;
	if (n == 0)
		return (0);
	while (str1[i] == str2[i] && i < n - 1)
	{
		if (i == n)
			return (0);
		i++;
	}
	return (str1[i] - str2[i]);
}
