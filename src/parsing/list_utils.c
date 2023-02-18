/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gclement <gclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 10:56:40 by gclement          #+#    #+#             */
/*   Updated: 2023/02/17 10:37:04 by gclement         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*new_node_cmd(char	*word, t_marks marks, t_type type, t_cmd **lst)
{
	t_cmd	*new;

	new = malloc(sizeof(t_cmd));
	if (!new)
		return (NULL);
	new->content = word;
	new->marks = marks;
	new->type = type;
	new->next = NULL;
	lst_cmd_add_back(lst, new);
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
