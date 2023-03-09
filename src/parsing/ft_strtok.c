/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaisne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 16:05:30 by gclement          #+#    #+#             */
/*   Updated: 2023/03/09 11:20:42 by gclement         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	word_count(char const *str, char *delimiters)
{
	int	i;
	int	count;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
	{
		if (ft_strchr(delimiters, str[i]) != 0)
			count++;
		i++;
	}
	if (ft_strchr(delimiters, str[i - 1]) == 0)
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

static void	put_value(unsigned int *i, int *row, size_t *start)
{
	*i = -1;
	*row = 0;
	*start = 0;
}

char	**ft_strtok(char const *str, char *delimiters)
{
	unsigned int	i;
	size_t			start;
	int				row;
	char			**ptr;

	put_value(&i, &row, &start);
	ptr = create_2d_array(word_count(str, delimiters));
	if (!ptr)
		return (NULL);
	while (str[++i])
	{
		if (ft_strchr(delimiters, str[i]) != 0)
		{
			ptr[row] = ft_substr(str, start, i - start);
			if (!ptr[row])
				return (free_2d_array(ptr), NULL);
			start = i + 1;
			row++;
		}
	}
	if (start < i)
	{
		ptr[row] = ft_substr(str, start, i - start);
			if (!ptr[row])
				return (free_2d_array(ptr), NULL);
		row++;
	}
	return (ptr[row] = NULL, ptr);
}
