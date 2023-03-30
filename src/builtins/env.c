/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaisne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 11:34:51 by jlaisne           #+#    #+#             */
/*   Updated: 2023/03/30 16:08:11 by jlaisne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

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

	env = malloc(sizeof(char *) * 3);
	if (!env)
		return (NULL);
	env = get_var_env(env, env_line);
	if (!env)
		return (NULL);
	return (env);
}

t_env	*duplicate_node(t_env* node) 
{
	t_env* new_node = malloc(sizeof(t_env));
	new_node->key = strdup(node->key); // duplicate the first string
	new_node->content = strdup(node->content); // duplicate the second string
	new_node->next = node->next; // set the next pointer to the same value as the original node

	return (new_node);
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
		ft_lstadd_back_env(env, ptr_env);
		ptr_exp = duplicate_node(ptr_env);
		ft_lstadd_back_env(exp, ptr_exp);
		if (!ptr_env) // || !ptr_exp
			exit_free(var);
		i++;
		free(tab);
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
	free_env_list(*add_env);
	return ;
}
