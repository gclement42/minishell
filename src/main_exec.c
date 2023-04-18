/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaisne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 14:23:08 by gclement          #+#    #+#             */
/*   Updated: 2023/04/18 14:46:14 by jlaisne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

unsigned char	g_return_status = 0;

void	init_struct(t_minish *var, char **envp)
{
	var->env_list = NULL;
	var->exp_list = NULL;
	var->oldpwd = NULL;
	var->env_tab = NULL;
	var->builtins = NULL;
	var->cd_path = NULL;
	var->var = NULL;
	var->cmd_lst = NULL;
	var->stdout_copy = -1;
	var->builtins = init_bultins_arr();
	termios_save(&var->orig_ter);
	set_env(var, envp, &(var->env_list), &(var->exp_list));
	modify_var(var, &(var->env_list), "_", "/usr/bin/env");
	set_shlvl(var, &(var->env_list), &(var->exp_list));
	var->var = malloc(sizeof(t_pipex));
	if (!var->var)
		exit_env(var);
}

int	main(int argc, char **argv, char *envp[])
{
	t_minish		*var;

	var = malloc(sizeof(t_minish));
	if (!var)
		exit(1);
	(void)argv;
	(void)argc;
	init_struct(var, envp);
	while (1)
	{
		if (init_sigaction(signal_handler_newl) == -1)
			exit_free(var);
		termios_disable_quit();
		var->cmd = readline("\033[1;31m minishell $> \033[0m");
		if (termios_restore(var->orig_ter) == 1)
			break ;
		if (var->cmd == NULL)
			exit_env(var);
		parsing(var->cmd, var);
		if (ft_strlen(var->cmd) > 0)
			add_history(var->cmd);
		free(var->cmd);
	}
	exit_env(var);
}
