/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoll.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaisne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 13:39:14 by jlaisne           #+#    #+#             */
/*   Updated: 2023/04/29 13:30:07 by jlaisne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	check_isspace(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] == ' ' || str[i] == '\t'
		|| str[i] == '\n' || str[i] == '\v'
		|| str[i] == '\f' || str[i] == '\r')
		i++;
	return (i);
}

long long	ft_atoll(const char *str)
{
	size_t		index;
	int			sign;
	long long	result;

	index = 0;
	sign = 1;
	result = 0;
	index = check_isspace(str);
	if ((str[index] == '+' || str[index] == '-')
		&& (str[index + 1] >= '0' && str[index + 1] <= '9'))
	{
		if (str[index] == '-')
			sign = -1;
		index++;
	}
	while (ft_isdigit(str[index]))
	{
		if ((result * 10 + (str[index] - '0') * sign) / 10 != result)
			return (0);
		result = result * 10 + (str[index] - '0') * sign;
		index++;
	}
	if (str[index] != '\0')
		return (0);
	return (result);
}
