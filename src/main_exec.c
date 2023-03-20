/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaisne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 14:23:08 by gclement          #+#    #+#             */
/*   Updated: 2023/03/20 13:37:54 by jlaisne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
unsigned char	return_status = 0;

void	init_struct(t_minish *var, char **envp)
{
	var->env_list = NULL;
	var->exp_list = NULL;
	set_env(envp, &(var->env_list), &(var->exp_list));
	modify_var(&(var->env_list), "_", "/usr/bin/env");
	set_shlvl(var, &(var->env_list), &(var->exp_list));
}

int	main(int argc, char **argv, char *envp[])
{
	t_minish		*var;
	struct	termios	orig_ter;

	var = malloc(sizeof(t_minish));
	if (!var)
		exit(1);
	(void)argv;
	(void)argc;
	var->builtins = init_bultins_arr();
	init_struct(var, envp);
	termios_save(&orig_ter);
	while (1)
	{
		init_sigaction(signal_handler_newl);
		termios_disable_quit();
		var->cmd = readline(">>");
		if (termios_restore(orig_ter) == 1)
			exit (1); //FREE
		if (var->cmd == NULL)
			exit_env();
		parsing(var->cmd, var);
		if (ft_strlen(var->cmd) > 0)
			add_history(var->cmd);
	}
}
