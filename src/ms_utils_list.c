/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_utils_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaisne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 14:08:19 by jlaisne           #+#    #+#             */
/*   Updated: 2023/03/31 14:09:43 by jlaisne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	print_list(t_env **list)
{
	t_env	*temp;

	temp = *list;
	if (!temp)
		return ;
	printf("%s=%s\n", temp->key, temp->content);
	while (temp->next != NULL)
	{
		temp = temp->next;
		printf("%s=%s\n", temp->key, temp->content);
	}
}

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

	if (!key || !content)
		return (NULL);
	ptr = (void *)malloc(sizeof(t_env));
	if (!ptr)
		return (NULL);
	ptr->key = key;
	ptr->content = content;
	ptr->next = NULL;
	return (ptr);
}

t_env	*duplicate_node(t_env* lst)
{
	t_env* new_node = malloc(sizeof(t_env));
	new_node->key = strdup(lst->key);
	new_node->content = strdup(lst->content);
	new_node->next = lst->next;

	return (new_node);
}
