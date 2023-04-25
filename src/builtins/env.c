/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaisne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 11:34:51 by jlaisne           #+#    #+#             */
/*   Updated: 2023/04/25 14:32:41 by jlaisne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static void	init_env(t_minish *var, t_env **env, t_env **exp)
{
	t_env	*key;
	t_env	*ptr;
	char	*cwd;

	cwd = get_cwd();
	key = ft_lstnew_env(ft_strdup("PWD"), ft_strdup(cwd));
	ptr = duplicate_node(key);
	if (!ptr || !key)
		exit_free(var);
	ft_lstadd_back_env(env, key);
	ft_lstadd_back_env(exp, ptr);
	key = ft_lstnew_env(ft_strdup("SHLVL"), ft_strdup("1"));
	ptr = duplicate_node(key);
	if (!ptr || !key)
		exit_free(var);
	ft_lstadd_back_env(env, key);
	ft_lstadd_back_env(exp, ptr);
	key = ft_lstnew_env(ft_strdup("_"), ft_strdup("/usr/bin/env"));
	ptr = duplicate_node(key);
	if (!ptr || !key)
		exit_free(var);
	ft_lstadd_back_env(env, key);
	ft_lstadd_back_env(exp, ptr);
}

char	**get_var_env(char **env, char *env_line)
{
	int		x;
	int		i;

	x = count_first_word(env_line, '=');
	i = 0;
	env[0] = malloc(sizeof(char) * x + 1);
	if (!env[0])
		return (NULL);
	while (i < x)
	{
		env[0][i] = env_line[i];
		i++;
	}
	env[0][i] = '\0';
	env[1] = ft_strdup(ft_strnstr_path(env_line, "=", ft_strlen(env_line)));
	if (!env[1])
		return (NULL);
	env[2] = NULL;
	return (env);
}

char	**split_env_var(char *env_line)
{
	char	**env;
	char	**env_tmp;

	env = malloc(sizeof(char *) * 3);
	if (!env)
		return (NULL);
	env_tmp = get_var_env(env, env_line);
	if (!env_tmp)
		return (free_2d_array(env), NULL);
	return (env_tmp);
}

void	set_env(t_minish *var, char **envp, t_env **env, t_env **exp)
{
	int		i;
	t_env	*ptr_env;
	t_env	*ptr_exp;
	char	**tab;

	i = 0;
	while (envp && envp[i])
	{
		tab = split_env_var(envp[i]);
		if (!tab)
			exit_free(var);
		ptr_env = ft_lstnew_env(tab[0], tab[1]);
		if (!ptr_env)
			return (free_2d_array(tab), exit_free(var));
		ft_lstadd_back_env(env, ptr_env);
		free_2d_array(tab);
		ptr_exp = duplicate_node(ptr_env);
		ft_lstadd_back_env(exp, ptr_exp);
		if (!ptr_env || !ptr_exp)
			exit_free(var);
		i++;
	}
	ptr_env = *env;
	if (!ptr_env)
		init_env(var, env, exp);
}

void	get_env(t_minish *var)
{
	print_list(&(var->env_list));
	return ;
}
