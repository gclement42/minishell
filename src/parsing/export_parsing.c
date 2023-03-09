/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_parsing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaisne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 18:35:39 by gclement          #+#    #+#             */
/*   Updated: 2023/03/09 11:08:00 by jlaisne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void export_parsing(t_minish *var, int argc, t_env *env, t_cmd *lst)
{
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
			break ;
		export_env(var, env, argc);
		env = env->next;
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
