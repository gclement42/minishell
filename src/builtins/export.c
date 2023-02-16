/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaisne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 16:21:07 by jlaisne           #+#    #+#             */
/*   Updated: 2023/02/16 11:02:41 by jlaisne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	add_export(t_minish *var, char *env_var)
{
	char	**key_var;
	t_env	*temp;
	t_env	*last;
	t_env	*ptr;
	int		len;
	
	key_var = ft_split(env_var, '=');
	if (!key_var)
		exit(1); //FREE
	if (key_var[1] == NULL)
	{
	 	key_var[1] = ft_strdup("''");
		if (!key_var[1])
			exit(1); //FREE
		// add to export list bc value not set
	}
	else
		add_var_env(var, key_var[0], key_var[1])
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
		return ;
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