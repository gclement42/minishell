/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_parsing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaisne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 18:35:39 by gclement          #+#    #+#             */
/*   Updated: 2023/05/04 11:35:46 by jlaisne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parsing_env(t_minish *var, t_cmd *lst)
{
	while (lst && lst->type != PIPE)
	{
		if (lst->type == OPT)
			return (msg_invalid_opt(lst->content, "env", 1));
		lst = lst->next;
	}
	get_env(var);
}

void	export_parsing(t_minish *var, int argc, t_env *env, t_cmd *lst)
{
	t_env	*tmp;
	int		b;

	if (argc == 0)
	{
		if (get_node(lst, OPT, PIPE))
			return ;
		export_env(var, env, 0, 0);
		return ;
	}
	while (lst && env)
	{
		lst = get_node(lst, ARG, PIPE);
		b = 0;
		if (check_is_valid_identifier(env->key, "export") == 0)
			return (free_env_list(env));
		if (ft_strchr(lst->content, '='))
			b = 1;
		tmp = env->next;
		env->next = NULL;
		export_env(var, env, argc, b);
		env = tmp;
		lst = lst->next;
	}
}

static void	unset_arg_parsing(t_minish *var, t_cmd *lst)
{
	while (lst)
	{
		if (lst->next && lst->next->type == ARG && \
			!ft_strchr(lst->content, ' '))
			lst->content = join_all_arg(lst, 1);
		if (ft_strchr(lst->content, '='))
		{
			ft_printf("minishell : unset : `%s' : not a valid identifier\n", \
				lst->content);
			g_return_status = 1;
			return ;
		}
		if (check_is_valid_identifier(lst->content, "unset") == 0)
			return ;
		remove_var_env(var, lst->content);
		while (lst && lst->type == ARG && !ft_strchr(lst->content, ' '))
			lst = lst->next;
		if (lst && lst->next)
			lst = lst->next;
	}
}

void	unset_parsing(t_minish *var, t_cmd *lst)
{
	t_cmd	*opt;

	if (!lst->next)
		return ;
	opt = get_node(lst, OPT, PIPE);
	if (opt)
		msg_invalid_opt(opt->content, "unset", 2);
	else if (lst->next && lst->next->content[0] == '_')
		return ;
	else
		unset_arg_parsing(var, lst);
}
