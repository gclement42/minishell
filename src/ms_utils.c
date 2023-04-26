/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gclement <gclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 13:13:28 by jlaisne           #+#    #+#             */
/*   Updated: 2023/04/24 16:18:53 by gclement         ###   ########.fr       */
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

size_t	count_first_word(char *env, char c)
{
	size_t	i;

	i = 0;
	while (env[i] != c)
		i++;
	return (i);
}

int	wordcount(char const *str, char c)
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

char	**lst_to_tab(t_env **lst)
{
	t_env	*temp;
	char	*hold;
	int		i;
	char	**tab;

	temp = *lst;
	i = 0;
	tab = malloc(sizeof(char *) * (ft_lstlen(*lst) + 1));
	if (!tab)
		return (NULL);
	while (temp)
	{
		hold = ft_strjoin(temp->key, "=");
		if (!hold)
			return (NULL);
		if (!temp->content)
			temp->content = " ";
		tab[i] = ft_strjoin(hold, temp->content);
		free(hold);
		if (!tab[i])
			return (NULL);
		i++;
		temp = temp->next;
	}
	return (tab[i] = '\0', tab);
}
