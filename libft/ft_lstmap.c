/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gclement <gclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 16:42:55 by gclement          #+#    #+#             */
/*   Updated: 2022/11/21 09:44:14 by gclement         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*tab;
	char	*str;

	if (!(*f) || !(*del))
		return (NULL);
	tab = NULL;
	while ((lst) != NULL)
	{
		str = (f)(lst->content);
		new = ft_lstnew(str);
		if (!new)
		{
			del(str);
			ft_lstclear(&tab, del);
			return (NULL);
		}
		ft_lstadd_back(&tab, new);
		lst = lst->next;
	}
	return (tab);
}
