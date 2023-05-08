/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ms_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gclement <gclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 14:58:09 by gclement          #+#    #+#             */
/*   Updated: 2023/05/08 13:50:11 by gclement         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	wordcount_split(char const *str, char c)
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

char	**create_2d_array(int row)
{
	char	**ptr;

	if (row < 0)
		return (NULL);
	ptr = malloc((row + 1) * sizeof(char *));
	if (!ptr)
		return (NULL);
	return (ptr);
}

int	count_len_split(int *bools, const char *s, char c, int i)
{
	int	l;

	l = i;
	while (s[l] && (s[l] != c || *bools == 0))
	{
		if (s[l] == '\'' || s[l] == '"')
			l += skip_quote(l, (char *)s, s[l]);
		else
			l++;
		if (ft_strlen(s) <= (size_t)l)
			break ;
		if (s[l] != ' ')
			*bools = 1;
	}
	return (l);
}

char	**put_value(char **ptr, const char *s, char c, int row)
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
		l += count_len_split(&bools, s, c, i) - i;
		if ((l - i) > 0)
		{
			bools = 0;
			ptr[row] = ft_substr(s, i, (l - i));
			if (!ptr[row])
				return (free_2d_array(&*ptr));
			row++;
		}
		i = l;
		if (ft_strlen(s) < i)
			break ;
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
		ptr[0] = (char *)ft_strdup(s);
		if (!ptr[0])
			return (free_2d_array(ptr), NULL);
		return (ptr[1] = NULL, ptr);
	}
	ptr = put_value(ptr, s, c, row);
	return (ptr);
}
