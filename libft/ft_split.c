/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gclement <gclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 13:57:20 by gclement          #+#    #+#             */
/*   Updated: 2023/04/24 13:37:22 by gclement         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	wordcount(char const *str, char c)
{
	size_t	i;
	int		count;

	if (str == NULL)
		return (0);
	count = 0;
	i = 0;
	while (i <= ft_strlen(str))
	{
		while (str[i] == c)
			i++;
		if (str[i] != c && str[i])
		{
			count++;
			while (str[i] != c && str[i])
				i++;
		}
		i++;
	}
	if (i > 0 && count == 0)
		count++;
	return (count);
}

static char	**create_2d_array(int row)
{
	char	**ptr;

	if (row < 0)
		return (NULL);
	ptr = malloc((row + 1) * sizeof(char *));
	if (!ptr)
		return (NULL);
	return (ptr);
}

static void	*free_array(char **ptr)
{
	int	i;

	i = 0;
	while (ptr[i])
	{
		free(ptr[i]);
		i++;
	}
	free(ptr);
	return (NULL);
}

static char	**put_value(char const *s, char c, char **ptr)
{
	unsigned int	i;
	size_t			l;
	int				row;
	char			*str;

	i = 0;
	row = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		l = i;
		while (s[l] != c && s[l])
			l++;
		if ((l - i) > 0)
		{
			str = ft_substr(s, i, (l - i));
			ptr[row] = str;
			if (!ptr[row++])
				return (free_array(&*ptr));
		}
		i = l;
	}
	return (ptr[row] = NULL, ptr);
}

char	**ft_split(char const *s, char c)
{
	char			**ptr;

	ptr = create_2d_array(wordcount(s, c));
	if (!ptr)
		return (NULL);
	ptr = put_value(s, c, ptr);
	return (ptr);
}
