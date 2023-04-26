/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_utils_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gclement <gclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 14:08:19 by jlaisne           #+#    #+#             */
/*   Updated: 2023/04/24 16:16:47 by gclement         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_lstadd_back_env(t_env **lst, t_env *new)
{
	t_env	*temp;

	temp = *lst;
	if (temp == NULL)
	{
		*lst = new;
		return ;
	}
	else
	{
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new;
	}
}

int	ft_lstlen(t_env *lst)
{
	int		x;
	t_env	*temp;

	x = 0;
	temp = lst;
	if (temp == NULL)
		return (x);
	else
	{
		x++;
		while (temp->next != NULL)
		{
			temp = temp->next;
			x++;
		}
	}
	return (x);
}

t_env	*ft_lstnew_env(char *key, char *content)
{
	t_env	*ptr;

	ptr = (void *)malloc(sizeof(t_env));
	if (!ptr)
		return (NULL);
	ptr->key = ft_strdup(key);
	ptr->content = ft_strdup(content);
	ptr->next = NULL;
	return (ptr);
}

t_env	*duplicate_node(t_env *lst)
{
	t_env	*new_node;

	new_node = malloc(sizeof(t_env));
	if (!new_node)
		return (NULL);
	new_node->key = strdup(lst->key);
	new_node->content = strdup(lst->content);
	new_node->next = lst->next;
	return (new_node);
}

t_env	*get_key_node(t_env *lst, char *key)
{
	t_env	*temp;
	int		len;

	temp = lst;
	len = ft_strlen(key);
	while (temp)
	{
		if (ft_strncmp(key, temp->key, len) == 0)
			break ;
		temp = temp->next;
	}
	if (temp && temp->key)
		return (temp);
	return (NULL);
}
