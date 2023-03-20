/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaisne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 15:16:10 by jlaisne           #+#    #+#             */
/*   Updated: 2023/03/17 16:09:21 by jlaisne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

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
			free(temp->key);
			free(temp->content);
			free(temp);
			return ;
		}
		prev = temp;
		temp = temp->next;
	}
	return_status = 0;
}
