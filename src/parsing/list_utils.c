/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gclement <gclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 10:56:40 by gclement          #+#    #+#             */
/*   Updated: 2023/04/06 14:50:44 by gclement         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	*new_node_cmd(char	*word, t_marks marks, t_type type, t_cmd **lst)
{
	t_cmd	*new;

	new = malloc(sizeof(t_cmd));
	if (!new)
		return (free(word), NULL);
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
