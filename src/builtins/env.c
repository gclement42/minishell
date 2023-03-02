/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gclement <gclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 11:34:51 by jlaisne           #+#    #+#             */
/*   Updated: 2023/02/28 14:08:28 by gclement         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

char	**get_var_env(char **env, char *env_line)
{
	int		x;
	int		i;
	
	env = malloc(sizeof(char *) * 3);
	if (!env)
		exit(1); // FREE
	x = count_fist_word(env_line);
	i = 0;
	env[0] = malloc(sizeof(char) * x + 1);
	if (!env[0])
		exit(1); //FREE
	while (i < x)
	{
		env[0][i] = env_line[i];
		i++;
	}
	env[0][i] = '\0';
	env[1] = ft_strdup(ft_strnstr_path(env_line, "=", ft_strlen(env_line)));
	if (!env[1])
		exit(1); //FREE
	env[2] = NULL;
	return (env);
}

char	**split_env_var(char *env_line)
{
	char	**env;
	int		i;

	env = ft_split(env_line, '=');
	if (!env)
		exit (1); // FREE
	i = 0;
	while (env[i])
		i++;
	if (i > 2)
	{
		free(env);
		env = get_var_env(env, env_line);
		return (env);
	}
	else
		return (env);
}

static void	init_env(t_env **env, t_env **exp)
{
	t_env	*key;
	t_env	*ptr;
	char	*cwd;

	cwd = get_cwd();
	key = ft_lstnew_env("PWD", cwd);
	ptr = ft_lstnew_env("PWD", cwd);
	if (!ptr || !key)
		exit(1); //FREE
	ft_lstadd_back_env(env, key);
	ft_lstadd_back_env(exp, ptr);
	key = ft_lstnew_env("SHLVL", "1");
	ptr = ft_lstnew_env("SHLVL", "1");
	if (!ptr || !key)
		exit(1); //FREE
	ft_lstadd_back_env(env, key);
	ft_lstadd_back_env(exp, ptr);
	key = ft_lstnew_env("_", "/usr/bin/env");
	ptr = ft_lstnew_env("OLDPWD", "");
	if (!ptr || !key)
		exit(1); //FREE
	ft_lstadd_back_env(env, key);
	ft_lstadd_back_env(exp, ptr);
}

void	set_env(char **envp, t_env **env, t_env **exp)
{
	int		i;
	char	**var_con;
	t_env	*ptr_env;
	t_env	*ptr_exp;

	i = 0;
	while (envp && envp[i])
	{
		var_con = split_env_var(envp[i]);
		ptr_env = ft_lstnew_env(var_con[0], var_con[1]);
		ptr_exp = ft_lstnew_env(var_con[0], var_con[1]);
		if (!ptr_env || !ptr_exp)
			exit(1); // FREE
		ft_lstadd_back_env(env, ptr_env);
		ft_lstadd_back_env(exp, ptr_exp);
		i++;
	}
	ptr_env = *env;
	if (!ptr_env)
		init_env(env, exp);
	else
		return ;
}

void	get_env(t_minish *var, t_env **add_env)
{
	print_list(&(var->env_list));
	print_list(add_env);
	return ;
}
