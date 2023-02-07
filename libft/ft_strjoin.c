/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gclement <gclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 10:02:16 by gclement          #+#    #+#             */
/*   Updated: 2022/11/16 09:57:13 by gclement         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*dest;

	if (!(s1 == NULL || s2 == NULL))
	{	
		dest = ft_calloc((ft_strlen(s1) + ft_strlen(s2) + 1),
				sizeof(char));
		if (!dest)
			return (NULL);
		ft_strlcpy(dest, ((char *)s1), (ft_strlen(s1) + 1));
		ft_strlcat(dest, s2, (ft_strlen(s1) + (ft_strlen(s2) + 1)));
		return (dest);
	}
	return (NULL);
}
