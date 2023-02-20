/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaisne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 15:16:10 by jlaisne           #+#    #+#             */
/*   Updated: 2023/02/16 15:37:07 by jlaisne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	remove_var_env(t_minish *var, char *unset_tab)
{
	t_env			*temp;
	t_env			*prev;
	unsigned int	len;

	temp = *(var->env_list);
	len = ft_strlen(unset_tab);
	prev = NULL;
	while (temp)
	{
		if (ft_strncmp(unset_tab, temp->key, len) == 0)
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

void	unset_env(t_minish *var)
{
	char	**unset_tab;
	int		i;
	
	i = 1;
	if (ft_strlen(var->cmd) == 5)
		return ;
	else
	{
		unset_tab = ft_split(var->cmd, ' ');
		if (!unset_tab)
			exit(1); //FREE
		while (unset_tab[i])
		{
			if (check_key(var->env_list, unset_tab[i]) == 0)
				remove_var_env(var, unset_tab[i]);
			else
				return ;
			i++;
		}
	}
}
