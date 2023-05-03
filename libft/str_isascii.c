/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_isascii.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaisne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 10:41:22 by jlaisne           #+#    #+#             */
/*   Updated: 2023/05/03 10:41:38 by jlaisne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	str_isascii(char *arg)
{
	int	index;

	index = 0;
	while (arg && arg[index])
	{
		if (ft_isascii(arg[index]) == 0)
			return (0);
		index++;
	}
	return (1);
}
