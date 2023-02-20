/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_utils_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaisne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 14:08:19 by jlaisne           #+#    #+#             */
/*   Updated: 2023/02/20 12:55:21 by jlaisne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_list(t_env *lst)
{
	t_env	*temp;

	while (lst)
	{
		temp = lst->next;
		free(lst);
		lst = temp;
	}
	free(lst);
}

void print_list(t_env **list)
{
	t_env	*temp;

	temp = *list;
	if (temp == NULL)
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

	ptr = (void *)malloc(sizeof(t_env));
	if (!ptr)
		return (NULL);
	ptr->key = key;
	ptr->content = content;
	ptr->next = NULL;
	return (ptr);
}
