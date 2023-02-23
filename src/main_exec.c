/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaisne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 14:23:08 by gclement          #+#    #+#             */
/*   Updated: 2023/02/20 13:01:27 by jlaisne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_struct(t_minish *var, char **envp)
{
	t_env	*env;
	t_env	*exp;

	env = NULL;
	exp = NULL;
	var->env_list = NULL;
	var->exp_list = NULL;
	set_env(var, envp, &env, &exp);
}

void	builtin_cmp(t_minish *var)
{
	if (ft_strncmp(var->cmd, "exit", 5) == 0)
	 	exit(0);
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
	if (ft_strncmp(var->cmd, "unset", 5) == 0)
	 	unset_env(var);
}


void	get_cmd_line(t_minish *var, t_env **lst)
{
	t_env	*temp;

	temp = *lst;
	while (temp)
	{
		if (ft_strnstr(temp->key, "PWD", 4))
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
			get_cmd_line(&var, var.env_list);
			var.cmd = readline(var.cmd_line);
			builtin_cmp(&var);
			if (ft_strlen(var.cmd) > 0)
			 	add_history(var.cmd);
			// free(var.cmd);
		}
	}
}