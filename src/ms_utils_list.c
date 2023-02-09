/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_utils_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaisne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 14:08:19 by jlaisne           #+#    #+#             */
/*   Updated: 2023/02/09 14:43:27 by jlaisne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

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

void print_list(t_env *list)
{
	printf("%s\n", list->content);
	while (list->next != NULL)
	{
		list = list->next;
		printf("%s\n", list->content);
	}
}

void	ft_lstadd_back_env(t_env **lst, t_env *new)
{
	t_env	*temp;

	temp = *lst;
	if ((*lst) == NULL)
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

t_env	*ft_lstnew_env(char *content)
{
	t_env	*ptr;

	ptr = (void *)malloc(sizeof(t_env));
	if (!ptr)
		return (NULL);
	ptr->content = content;
	ptr->next = NULL;
	return (ptr);
}