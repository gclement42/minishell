/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gclement <gclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 10:52:24 by gclement          #+#    #+#             */
/*   Updated: 2022/11/16 16:52:08 by gclement         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	set_srchbeg(char const *str, char const *set)
{
	int		x;
	size_t	i;
	int		count;

	i = 0;
	count = 0;
	x = 0;
	while (i < ft_strlen(str))
	{
		while (set[x])
		{
			if (str[i] == set[x])
			{
				count++;
				i++;
				x = 0;
			}
			else
				x++;
		}
		i++;
	}
	return (count);
}

static unsigned int	set_srchend(char const *str, char const *set)
{
	int	x;
	int	i;
	int	count;

	i = ft_strlen(str);
	count = 0;
	i--;
	x = 0;
	while (i >= 0)
	{
		while (set[x])
		{
			if (str[i] == set[x])
			{
				count++;
				i--;
				x = 0;
			}
			else
				x++;
		}
		i--;
	}
	return (count);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char		*ptr;
	size_t		begin;
	int			l;

	if (s1 == NULL)
		return (NULL);
	begin = set_srchbeg(s1, set);
	if (begin < ft_strlen(s1))
	{
		l = (ft_strlen(s1) - begin - set_srchend(s1, set));
		ptr = ft_substr(s1, begin, l);
	}
	else
		ptr = ft_calloc(1, sizeof(char));
	if (!ptr)
		return (NULL);
	return (ptr);
}
