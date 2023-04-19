/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaisne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 10:56:40 by gclement          #+#    #+#             */
/*   Updated: 2023/04/19 10:08:39 by jlaisne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	*new_node_cmd(char	*word, t_marks marks, t_type type, t_cmd **lst)
{
	t_cmd	*new;

	if (!word)
		return (NULL);
	new = malloc(sizeof(t_cmd));
	if (!new)
	{
		if (type != S_SPACES && type != PIPE)
			free(word);
		return (NULL);
	}
	new->content = ft_strdup(word);
	if (!new->content)
		return (NULL);
	new->marks = marks;
	new->type = type;
	new->next = NULL;
	lst_cmd_add_back(lst, new);
	if (type != S_SPACES && type != PIPE)
		free(word);
	return (lst);
}

t_cmd	*cmd_lst_last(t_cmd **lst)
{
	t_cmd	*tmp;

	if (!*lst)
		return (NULL);
	tmp = *lst;
	while (tmp->next)
		tmp = tmp->next;
	return (tmp);
}

void	lst_cmd_add_back(t_cmd **lst, t_cmd *new)
{
	t_cmd	*head;

	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	head = cmd_lst_last(lst);
	head->next = new;
}

t_cmd	*get_node(t_cmd *lst, t_type type, t_type end)
{
	if (!lst)
		return (NULL);
	while (lst && lst->type != type && lst->type != end)
		lst = lst->next;
	if (lst && lst->type == type)
		return (lst);
	else
		return (NULL);
}

int	count_type_in_lst(t_cmd *lst, t_type type, t_type delimiter)
{
	int	count;

	count = 0;
	if (!lst)
		return (0);
	while (lst && lst->type != delimiter)
	{
		if (lst->type == type)
			count++;
		lst = lst->next;
	}
	return (count);
}
