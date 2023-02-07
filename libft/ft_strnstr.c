/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gclement <gclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 13:29:45 by gclement          #+#    #+#             */
/*   Updated: 2022/11/16 15:31:55 by gclement         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	x;

	i = 0;
	if (haystack == NULL && len == 0)
		return (NULL);
	if (needle[0] == '\0')
		return (&((char *)haystack)[i]);
	x = 0;
	while (haystack[i] && i < len && i + x < len)
	{
		x = 0;
		while (haystack[i + x] == needle[x] && needle[x] && i + x < len)
			x++;
		if (needle[x] == '\0')
			return (&((char *)haystack)[i]);
		i++;
	}
	return (NULL);
}
