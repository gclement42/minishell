/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaisne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 14:23:08 by gclement          #+#    #+#             */
/*   Updated: 2023/02/16 10:57:36 by jlaisne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_struct(t_minish *var, char **envp)
{
	t_env	*env;

	env = NULL;
	var->env_list = NULL;
	set_env(var, &env, envp);
}

void	unset_env(t_minish *var)
{
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
	if (ft_strncmp(var->cmd, "cd ", 2) == 0)
		cd(var);
	if (ft_strncmp(var->cmd, "pwd", 3) == 0)
		get_pwd(var);
	if (ft_strncmp(var->cmd, "env", 3) == 0)
		get_env(var);
	if (ft_strncmp(var->cmd, "echo", 4) == 0)
		print_echo(0, var->cmd);
	if (ft_strncmp(var->cmd, "export", 6) == 0)
		export_env(var, 2);
	// if (ft_strncmp(var->cmd, "unset", 6) == 0)
	// 	unset_env(var);
}


void	get_cmd_line(t_minish *var)
{
	t_env	*temp;

	temp = *(var->env_list);
	while (temp)
	{
		if (ft_strnstr(temp->key, "PWD", 3))
			break;
		temp = temp->next;
	}
	var->cmd_line = ft_strjoin(temp->content, "$ ");
	if (!var->cmd_line)
		exit(1); //FREE
}

int	main(int argc, char **argv, char *envp[])
{
	t_minish	var;

	(void)argv;
	if (argc == 1)
	{
		init_struct(&var, envp);
		while (1)
		{
			get_cmd_line(&var);
			var.cmd = readline(var.cmd_line);
			builtin_cmp(&var);
			if (ft_strlen(var.cmd) > 0)
			 	add_history(var.cmd);
			// free(var.cmd);
		}
	}
}