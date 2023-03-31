/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaisne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 14:23:08 by gclement          #+#    #+#             */
/*   Updated: 2023/03/31 13:41:17 by jlaisne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
unsigned char	return_status = 0;

void	init_struct(t_minish *var, char **envp)
{
	var->env_list = NULL;
	var->exp_list = NULL;
	var->oldpwd = NULL;
	var->env_tab = NULL;
	var->builtins = NULL;
	set_env(var, envp, &(var->env_list), &(var->exp_list));
	modify_var(var, &(var->env_list), "_", "/usr/bin/env");
	set_shlvl(var, &(var->env_list), &(var->exp_list));
}

int	main(int argc, char **argv, char *envp[])
{
	t_minish		*var;
	struct	termios	orig_ter;
	int				run;
	
	run = 1;
	var = malloc(sizeof(t_minish));
	if (!var)
		exit(1);
	(void)argv;
	(void)argc;
	init_struct(var, envp);
	var->builtins = init_bultins_arr();
	termios_save(&orig_ter);
	while (run)
	{
		init_sigaction(signal_handler_newl);
		termios_disable_quit();
		var->cmd = readline(">>");
		if (termios_restore(orig_ter) == 1)
			run = 0; //FREE
		if (var->cmd == NULL)
			exit_env(var);
		parsing(var->cmd, var);
		if (ft_strlen(var->cmd) > 0)
			add_history(var->cmd);
		free(var->cmd);
	}
	exit_env(var);
}
