/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaisne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 16:21:07 by jlaisne           #+#    #+#             */
/*   Updated: 2023/02/20 13:00:15 by jlaisne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	add_export(t_minish *var, char *env_var)
{
	char	**key_var;
	
	key_var = ft_split(env_var, '=');
	if (!key_var)
		exit(1); //FREE
	if (!key_var[1])
	{
	 	key_var[1] = ft_strdup("''");
		if (!key_var[1])
			exit(1); //FREE
		add_var_env(var->exp_list, key_var[0], key_var[1]);
	}
	else
	{
		add_var_env(var->env_list, key_var[0], key_var[1]);
		add_var_env(var->exp_list, key_var[0], key_var[1]);
	}
}

void	export_env(t_minish *var, int arg)
{
	int		i;
	char	**export_tab;

	i = 1;
	export_tab = ft_split(var->cmd, ' ');
	if (!export_tab)
		exit(1); //FREE
	if (arg == 1)
	{
		print_list(var->exp_list);
		return ;
	}
	else
	{
		while (arg > 1)
		{
			add_export(var, export_tab[i]);
			arg--;
			i++;
		}
	}
}