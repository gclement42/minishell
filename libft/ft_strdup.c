/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gclement <gclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 17:16:10 by gclement          #+#    #+#             */
/*   Updated: 2022/11/17 09:47:03 by gclement         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup( const char *source )
{
	char	*ptr;
	int		i;
	size_t	len;

	i = 0;
	len = (size_t)ft_strlen(source);
	ptr = ft_calloc((len + 1), sizeof(char));
	if (!ptr)
		return (NULL);
	while (0 < len)
	{
		ptr[i] = source[i];
		len--;
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}
