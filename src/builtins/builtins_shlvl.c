/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_shlvl.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaisne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 14:06:42 by jlaisne           #+#    #+#             */
/*   Updated: 2023/03/31 16:56:04 by jlaisne          ###   ########.fr       */
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

static void	create_shlvl(t_minish *var, t_env **env_l, t_env **exp_l)
{
	t_env	*key;
	t_env	*ptr;

	key = ft_lstnew_env(ft_strdup("SHLVL"), ft_strdup("1"));
	ptr = duplicate_node(key);
	if (!ptr || !key)
		exit_free(var);
	ft_lstadd_back_env(env_l, key);
	ft_lstadd_back_env(exp_l, ptr);
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
				modify_var(var, &temp_env, "SHLVL", str_lvl);
				modify_var(var, &temp_exp, "SHLVL", str_lvl);
				free(str_lvl);
			}
			temp_env = temp_env->next;
		}
	}
	else
		create_shlvl(var, env_l, exp_l);
}

static void	init_shlvl(t_env **exp_l, t_env **env_l, t_env *new_var, t_minish *var)
{
	t_env	*key;
	t_env	*ptr;
	char	*str_lvl;

	var->lvl = ft_atoi(new_var->content);
	var->lvl++;
	var->lvl = set_strlvl(var->lvl);
	str_lvl = ft_itoa(var->lvl);
	if (!str_lvl)
		exit_free(var);
	key = ft_lstnew_env(ft_strdup("SHLVL"), str_lvl);
	ptr = duplicate_node(key);
	if (!ptr || !key)
		exit_free(var);
	ft_lstadd_back_env(env_l, ptr);
	ft_lstadd_back_env(exp_l, ptr);
	free(str_lvl);
}

void	modify_shlvl(t_env **exp_l, t_env **env_l, t_env *new_var, t_minish *var)
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
				var->lvl = ft_atoi(new_var->content);
				var->lvl++;
				var->lvl = set_strlvl(var->lvl);
				str_lvl = ft_itoa(var->lvl);
				if (!str_lvl)
					exit_free(var);
				modify_var(var, &temp_env, "SHLVL",  str_lvl);
				modify_var(var, &temp_exp, "SHLVL", str_lvl);
				free(str_lvl);
			}
			temp_env = temp_env->next;
		}
	}
	else
		init_shlvl(exp_l, env_l, new_var, var);
}
