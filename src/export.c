/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaisne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 14:23:08 by gclement          #+#    #+#             */
/*   Updated: 2023/02/09 15:43:41 by jlaisne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

t_env	**set_env(t_minish *var, t_env **env)
{
	int		i;
	t_env *ptr;

	i = 0;
	ptr = NULL;
	if (var->env_tab)
	{
		while (var->env_tab[i])
		{
			ptr = ft_lstnew_env(var->env_tab[i]);
			if (!ptr)
				return (NULL);
			ft_lstadd_back_env(env, ptr);
			i++;
		}
	}
	return(env);
}

void	init_struct(t_minish *var, char **envp)
{
	t_env	*env;

	env = NULL;
	var->env_list = NULL;
	var->cmd = readline(">> ");
	var->env_tab = envp;
	var->env_list = set_env(var, &env);
	if (!var->env_list)
	{
		free(var->cmd);
		exit(1);
	}
}

void	get_pwd(t_minish *var)
{
	t_env	*temp;

	temp = *(var->env_list);
	var->pwd = NULL;
	while (temp)
	{
		if (ft_strnstr(temp->content, "PWD=", 5))
			break;
		temp = temp->next;
	}
	var->pwd = ft_strdup(ft_strnstr_path(temp->content, "PWD=", ft_strlen(temp->content)));
	printf("%s\n", var->pwd);
	free(var->pwd);
}

void	get_env(t_minish *var)
{
	print_list(*(var->env_list));
	return ;
}

void	export_env(t_minish *var)
{
	(void)var;
	return ;
}

void	unset_env(t_minish *var)
{
	int	i;

	i = 1;
	if (ft_strlen(var->cmd) == 5)
	{
		ft_putstr_fd("unset: not enough arguments\n", 2);
		return ;
	}
	else
	{
		var->unset_tab = ft_split(var->cmd, ' ');
		if (!var->unset_tab)
		{
			free(var->cmd);
			free_list(*(var->env_list));
			exit(1);
		}
	}
}

void	builtin_cmp(t_minish *var)
{
		if (ft_strncmp(var->cmd, "exit", 5) == 0)
		{
			free(var->cmd);
			free_list(*(var->env_list));
			exit(0);
		}
		if (ft_strncmp(var->cmd, "pwd", 4) == 0)
			get_pwd(var);
		if (ft_strncmp(var->cmd, "env", 4) == 0)
			get_env(var);
		if (ft_strncmp(var->cmd, "unset", 6) == 0)
			unset_env(var);
		// if (ft_strncmp(var->cmd, "export", 7) == 0)
		// 	export_env(var);
		// if (ft_strncmp(cmd, "exit", 5) == 0)
		// if (ft_strncmp(cmd, "exit", 5) == 0)
		// if (ft_strncmp(cmd, "exit", 5) == 0)	
}

int	main(int argc, char **argv, char *envp[])
{
	t_minish	var;

	(void)argv;
	if (argc == 1)
	{
		while (1)
		{
			init_struct(&var, envp);
			builtin_cmp(&var);
			if (ft_strlen(var.cmd) > 0)
				add_history(var.cmd);
			free(var.cmd);
			if (var.env_list)
				free_list(*(var.env_list));
			// rl_redisplay();
			// rl_clear_history();
			// rl_on_new_line();
		}
	}
}