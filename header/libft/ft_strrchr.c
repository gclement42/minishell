/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gclement <gclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 11:18:33 by gclement          #+#    #+#             */
/*   Updated: 2022/11/16 15:19:32 by gclement         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *string, int searchedCh)
{
	int	str_len;

	str_len = ft_strlen(string);
	while (str_len > 0)
	{
		if (string[str_len] == (char)searchedCh)
			return (&((char *)string)[str_len]);
		str_len--;
	}
	if (string[str_len] == (char)searchedCh)
		return (&((char *)string)[str_len]);
	return (0);
}
