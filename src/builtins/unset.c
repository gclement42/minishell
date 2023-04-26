/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaisne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 15:16:10 by jlaisne           #+#    #+#             */
/*   Updated: 2023/04/24 10:04:08 by jlaisne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static void	free_node(t_env *lst)
{
	if (lst->key)
		free(lst->key);
	if (lst->content)
		free(lst->content);
	free(lst);
}

void	remove_var_export(t_minish *var, char *unset_tab)
{
	t_env			*temp;
	t_env			*prev;
	unsigned int	len;

	temp = var->exp_list;
	len = ft_strlen(unset_tab);
	prev = NULL;
	while (temp)
	{
		if (ft_strncmp(unset_tab, temp->key, len + 1) == 0)
		{
			prev->next = temp->next;
			free_node(temp);
			break ;
		}
		prev = temp;
		temp = temp->next;
	}
	g_return_status = 0;
}

void	remove_var_env(t_minish *var, char *unset_tab)
{
	t_env			*temp;
	t_env			*prev;
	unsigned int	len;

	temp = var->env_list;
	len = ft_strlen(unset_tab);
	prev = NULL;
	while (temp)
	{
		if (ft_strncmp(unset_tab, temp->key, len + 1) == 0)
		{
			prev->next = temp->next;
			free_node(temp);
			break ;
		}
		prev = temp;
		temp = temp->next;
	}
	remove_var_export(var, unset_tab);
	g_return_status = 0;
}
