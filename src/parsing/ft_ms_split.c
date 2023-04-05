/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ms_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaisne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 14:58:09 by gclement          #+#    #+#             */
/*   Updated: 2023/04/05 14:08:52 by jlaisne          ###   ########.fr       */
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

static char	**put_value(char **ptr, const char *s, char c, int row)
{
	int				l;
	unsigned int	i;

	i = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		l = i;
		while (s[l] && s[l] != c)
		{
			if (s[l] == '\'' || s[l] == '"')
				skip_quote(&l, (char *)s, s[l]);
			l++;
		}	
		if ((l - i) > 0)
		{
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
	ptr = put_value(ptr, s, c, row);
	return (ptr);
}
