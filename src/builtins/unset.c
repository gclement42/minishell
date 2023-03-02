/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gclement <gclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 15:16:10 by jlaisne           #+#    #+#             */
/*   Updated: 2023/03/01 11:03:32 by gclement         ###   ########.fr       */
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
}

// void	unset_env(t_minish *var, t_env *unset_var)
// {
// 	char	**unset_tab;

// 	if (check_key(&(var->env_list), unset_var->key) == 0)
// 		remove_var_env(var, unset_var->key);
// 	else
// 		return ;
// }
