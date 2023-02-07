/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gclement <gclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 09:14:32 by gclement          #+#    #+#             */
/*   Updated: 2022/11/16 09:22:28 by gclement         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	x;
	size_t	dest_l;
	size_t	src_l;

	if (dest == NULL && size == 0)
		return (0);
	dest_l = ft_strlen(dest);
	src_l = ft_strlen(src);
	x = 0;
	i = dest_l;
	if (size <= dest_l)
		return (src_l + size);
	if (size > 0)
	{
		while (src[x] && (x < size - dest_l - 1))
		{
			dest[i] = src[x];
			i++;
			x++;
		}
		dest[i] = '\0';
	}
	return (dest_l + src_l);
}
