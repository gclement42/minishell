/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaisne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 14:23:08 by gclement          #+#    #+#             */
/*   Updated: 2023/02/21 15:06:43 by jlaisne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_struct(t_minish *var, char **envp)
{
	var->env_list = NULL;
	var->exp_list = NULL;
	set_env(envp, &(var->env_list), &(var->exp_list));
	modify_var(&(var->env_list), "_", "/usr/bin/env");
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
	if (ft_strncmp(var->cmd, "export", 7) == 0)
	 	export_env(var);
	if (ft_strncmp(var->cmd, "unset", 5) == 0)
	 	unset_env(var);
}

int	main(int argc, char **argv, char *envp[])
{
	t_minish	*var;

	(void)argv;
	var = malloc(sizeof(t_minish));
	if (!var)
		exit(1);
	if (argc == 1)
	{
		init_struct(var, envp);
		while (1)
		{
			var->cmd = readline(">>");
			builtin_cmp(var);
			if (ft_strlen(var->cmd) > 0)
			 	add_history(var->cmd);
			// free(var.cmd);
		}
	}
}