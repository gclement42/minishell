/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gclement <gclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 09:31:29 by gclement          #+#    #+#             */
/*   Updated: 2022/11/17 11:03:50 by gclement         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*dst;

	if (s != NULL)
	{	
		if (len > ft_strlen(s))
			len = ft_strlen(s);
		dst = ft_calloc((len + 1), sizeof(char));
		if (!dst)
			return (NULL);
		if (ft_strlen(s) <= start)
			return (dst);
		ft_strlcpy(dst, &s[start], (len + 1));
		return (dst);
	}
	return (NULL);
}
