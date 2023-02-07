/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gclement <gclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 12:23:55 by gclement          #+#    #+#             */
/*   Updated: 2022/11/16 15:08:03 by gclement         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *memBlock, int srchChar, size_t size)
{
	char	*str;
	size_t	i;

	str = ((char *)memBlock);
	i = 0;
	if (size <= 0)
		return (NULL);
	while (i < size)
	{
		if (((char)srchChar) == str[i])
			return (&str[i]);
		i++;
	}
	return (0);
}
