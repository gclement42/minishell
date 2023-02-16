/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaisne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 11:34:51 by jlaisne           #+#    #+#             */
/*   Updated: 2023/02/16 10:35:53 by jlaisne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static void	init_env(t_minish *var, t_env **env)
{
	var->env_list = env;
}

void	set_env(t_minish *var, t_env **env, char **envp)
{
	int		i;
	char	**var_con;
	t_env	*key;
	
	i = 0;
	key = NULL;
	if (envp)
	{
		while (envp && envp[i])
		{
			var_con = split_env_var(envp[i]);
			key = ft_lstnew_env(var_con[0], var_con[1]);
			if (!key)
				return ;
			ft_lstadd_back_env(env, key);
			i++;
		}
	}
	if (env)
		var->env_list = env;
	else
		init_env(var, env);
}

void	get_env(t_minish *var)
{
	print_list(var->env_list);
	return ;
}
