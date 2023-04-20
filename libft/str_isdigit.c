/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_isdigit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaisne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 09:50:50 by jlaisne           #+#    #+#             */
/*   Updated: 2023/04/20 09:56:35 by jlaisne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	str_isdigit(char *arg)
{
	int	index;

	index = 0;
	while (arg[index])
	{
		if (ft_isdigit(arg[index]) == 0)
			return (0);
		index++;
	}
	return (1);
}
