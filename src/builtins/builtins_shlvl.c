/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_shlvl.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaisne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 14:06:42 by jlaisne           #+#    #+#             */
/*   Updated: 2023/03/30 15:44:19 by jlaisne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static int	set_strlvl(int	strlvl)
{
	if (strlvl > 999 && strlvl < 99999999)
		strlvl = 999;
	else if (strlvl > 99999999)
		strlvl = 1;
	else if (strlvl < 0)
		strlvl = 0;
	return (strlvl);
}

void	set_shlvl(t_minish *var, t_env **env_l, t_env **exp_l)
{
	t_env	*temp_env;
	t_env	*temp_exp;
	char	*str_lvl;

	temp_env = *env_l;
	temp_exp = *exp_l;
	if (check_key(&temp_env, "SHLVL") == 0)
	{
		while (temp_env)
		{
			if (ft_strnstr(temp_env->key, "SHLVL", 6))
			{
				var->lvl = ft_atoi(temp_env->content);
				var->lvl++;
				var->lvl = set_strlvl(var->lvl);
				str_lvl = ft_itoa(var->lvl);
				if (!str_lvl)
					exit_free(var); //FREE
				modify_var(&temp_env, "SHLVL", str_lvl);
				modify_var(&temp_exp, "SHLVL", str_lvl);
				// free(str_lvl);
				break ;
			}
			temp_env = temp_env->next;
		}
	}
}

static void	init_shlvl(t_env **exp_l, t_env **env_l, t_env *new_var, t_minish *var)
{
	char	*str_lvl;
	t_env	*key;
	t_env	*ptr;

	var->lvl = ft_atoi(new_var->content);
	var->lvl++;
	var->lvl = set_strlvl(var->lvl);
	str_lvl = ft_itoa(var->lvl);
	if (!str_lvl)
		exit_free(var); //FREE
	key = ft_lstnew_env("SHLVL", str_lvl);
	ptr = ft_lstnew_env("SHLVL", str_lvl);
	if (!ptr || !key)
		exit_free(var); //FREE
	ft_lstadd_back_env(env_l, key);
	ft_lstadd_back_env(exp_l, ptr);
}

void	modify_shlvl(t_env **exp_l, t_env **env_l, t_env *new_var, t_minish *var)
{
	char	*str_lvl;
	t_env	*temp_env;
	t_env	*temp_exp;

	temp_env = *env_l;
	temp_exp = *exp_l;
	if (check_key(&temp_env, "SHLVL") == 0)
	{
		while (temp_env)
		{
			if (ft_strnstr(temp_env->key, "SHLVL", 6))
			{
				var->lvl = ft_atoi(new_var->content);
				var->lvl++;
				var->lvl = set_strlvl(var->lvl);
				str_lvl = ft_itoa(var->lvl);
				if (!str_lvl)
					exit(1); //FREE
				modify_var(&temp_env, "SHLVL", str_lvl);
				modify_var(&temp_exp, "SHLVL", str_lvl);
				free(str_lvl);
			}
			temp_env = temp_env->next;
		}
	}
	else
		init_shlvl(exp_l, env_l, new_var, var);
}
