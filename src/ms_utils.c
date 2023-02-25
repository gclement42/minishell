/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaisne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 13:13:28 by jlaisne           #+#    #+#             */
/*   Updated: 2023/02/15 13:54:45 by jlaisne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strnstr_path(char *haystack, char *needle, size_t len)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	j = 0;
	if (needle[j] == '\0')
		return ((char *)haystack);
	if (len == 0 && haystack == NULL)
		return (NULL);
	while (haystack[i] != '\0' && i <= len)
	{
		if (haystack[i] == needle[0])
		{
			j = 0;
			while (needle[j] && (haystack[i + j] == needle[j])
				&& ((i + j) < len))
				j++;
			if (needle[j] == '\0')
				return ((char *)&haystack[i + j]);
		}
		i++;
	}
	return (NULL);
}

void	*free_array(char **ptr)
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

int	count_fist_word(char *env)
{
	int	i;

	i = 0;
	while (env[i] != '=')
		i++;
	return (i);
}
