/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaisne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 13:13:28 by jlaisne           #+#    #+#             */
/*   Updated: 2023/03/09 10:10:35 by gclement         ###   ########.fr       */
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
	int		len;
	int		i;
	char	**tab;

	temp = *lst;
	len = ft_lstlen(*lst);
	i = 0;
	tab = malloc(sizeof(char *) * (len + 1));
	if (!tab)
		return (NULL);
	while (temp)
	{
		hold = ft_strjoin(temp->key, "=");
		if (!hold)
			return(NULL);
		tab[i] = ft_strjoin(hold, temp->content);
		if (!tab[i])
			return(NULL);
		i++;
		temp = temp->next;
	}
	tab[i] = '\0';
	return (tab);
}
