/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ms_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gclement <gclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 14:58:09 by gclement          #+#    #+#             */
/*   Updated: 2023/04/13 08:41:15 by gclement         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	wordcount_split(char const *str, char c)
{
	size_t	i;
	int		count;

	if (str == NULL)
		return (0);
	count = 0;
	i = 0;
	while (i <= ft_strlen(str))
	{
		while (str[i] && str[i] == c)
			i++;
		if (str[i] && str[i] != c)
		{
			count++;
			while (str[i] && str[i] != c)
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

static	int	count_len_split(int *bools, const char *s, char c, int i)
{
	int	l;

	l = 0;
	while (s[i] && (s[i] != c || *bools == 0))
	{
		if (s[i] == '\'' || s[i] == '"')
		{
			skip_quote(&i, (char *)s, s[i]);
			l += i - l;
		}
		if (!s[i])
			break ;
		if (s[i] != ' ')
			*bools = 1;
		l++;
		i++;
	}
	return (l);
}

static char	**put_value(char **ptr, const char *s, char c, int row)
{
	int				l;
	unsigned int	i;
	int				bools;

	i = 0;
	bools = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		l = i;
		l += count_len_split(&bools, s, c, i);
		if ((l - i) > 0)
		{
			bools = 0;
			ptr[row] = ft_substr(s, i, (l - i));
			if (!ptr[row++])
				return (free_2d_array(&*ptr));
		}
		i = l;
	}
	return (ptr[row] = NULL, ptr);
}

char	**ft_ms_split(char const *s, char c)
{
	int				row;
	char			**ptr;

	row = 0;
	ptr = create_2d_array(wordcount_split(s, c));
	if (!ptr)
		return (NULL);
	if (wordcount_split(s, c) == 1 && s[ft_strlen(s) - 1] == '|')
	{
		ptr[0] = (char *)s;
		return (ptr[1] = NULL, ptr);
	}
	ptr = put_value(ptr, s, c, row);
	return (ptr);
}
