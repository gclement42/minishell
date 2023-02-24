/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gclement <gclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 09:30:58 by gclement          #+#    #+#             */
/*   Updated: 2022/11/13 13:45:18 by gclement         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t size)
{
	if (((char *)dest) < ((char *)src))
		return (ft_memcpy(dest, src, size));
	if (!dest && !src)
	{
		return (NULL);
	}
	while (0 < size)
	{
		((char *)dest)[size - 1] = ((char *)src)[size - 1];
		size--;
	}
	return (dest);
}
