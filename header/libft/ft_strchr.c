/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gclement <gclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 10:05:49 by gclement          #+#    #+#             */
/*   Updated: 2022/11/29 10:07:04 by gclement         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char	*string, int searchCh)
{
	int	i;

	i = 0;
	while (string[i])
	{
		if (string[i] == (char)searchCh)
			return (&((char *)string)[i]);
		i++;
	}
	if (string[i] == (char)searchCh)
		return (&((char *)string)[i]);
	return (0);
}
