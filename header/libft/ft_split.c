/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gclement <gclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 13:57:20 by gclement          #+#    #+#             */
/*   Updated: 2023/01/07 14:30:43 by gclement         ###   ########.fr       */
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

static void	put_value(unsigned int *i, int *row)
{
	*i = 0;
	*row = 0;
}

char	**ft_split(char const *s, char c)
{
	unsigned int	i;
	size_t			l;
	int				row;
	char			**ptr;

	put_value(&i, &row);
	ptr = create_2d_array(wordcount(s, c));
	if (!ptr)
		return (NULL);
	while (s[i])
	{
		while (s[i] == c)
			i++;
		l = i;
		while (s[l] != c && s[l])
			l++;
		if ((l - i) > 0)
		{
			ptr[row] = ft_substr(s, i, (l - i));
			if (!ptr[row++])
				return (free_array(&*ptr));
		}
		i = l;
	}
	return (ptr[row] = NULL, ptr);
}
