/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_parsing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gclement <gclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 18:35:39 by gclement          #+#    #+#             */
/*   Updated: 2023/03/20 13:31:13 by gclement         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void export_parsing(t_minish *var, int argc, t_env *env, t_cmd *lst)
{
	t_env *tmp;
	
	if (!env || env->key[0] == '#')
	{
		if (lst && check_is_valid_identifier(lst->content, "export") == 0)
			return ;
		export_env(var, env, 0);
		return ;
	}
	while (env && lst && lst->type != PIPE)
	{
		if (check_is_valid_identifier(lst->content, "export") == 0)
			return ;
		tmp = env->next;
		env->next = NULL;
		export_env(var, env, argc);
		env = tmp;
		lst = lst->next;
	}
}

void	unset_parsing(t_minish *var, t_cmd *lst)
{
	while (lst)
	{
		check_is_valid_identifier(lst->content, "unset");
		remove_var_env(var, lst->content);
		lst = lst->next;
	}
}
