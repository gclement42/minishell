/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaisne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 14:23:08 by gclement          #+#    #+#             */
/*   Updated: 2023/04/20 14:46:22 by jlaisne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// unsigned char	g_env->return_status = 0;
t_minish		*g_env = NULL;

static void	init_struct(char **envp)
{
	g_env->env_list = NULL;
	g_env->exp_list = NULL;
	g_env->oldpwd = NULL;
	g_env->env_tab = NULL;
	g_env->builtins = NULL;
	g_env->cd_path = NULL;
	g_env->pipex = NULL;
	g_env->cmd_lst = NULL;
	g_env->cmd = NULL;
	g_env->stdout_copy = -1;
	g_env->builtins = init_bultins_arr();
	termios_save(&g_env->orig_ter);
	set_env(g_env, envp, &(g_env->env_list), &(g_env->exp_list));
	modify_var(g_env, &(g_env->env_list), "_", "/usr/bin/env");
	set_shlvl(g_env, &(g_env->env_list), &(g_env->exp_list));
	g_env->pipex = malloc(sizeof(t_pipex));
	if (!g_env->pipex)
		exit_env(g_env);
}

int	main(int argc, char **argv, char *envp[])
{
	// t_minish		*var;
	g_env = NULL;
	g_env = malloc(sizeof(t_minish));
	if (!g_env)
		exit(1);
	(void)argv;
	(void)argc;
	init_struct(envp);
	while (1)
	{
		if (init_sigaction(signal_handler_newl) == -1)
			exit_free(g_env);
		if (termios_disable_quit() == 1)
			break ;
		g_env->cmd = readline("\033[1;31m minishell $> \033[0m");
		if (termios_restore(g_env->orig_ter) == 1)
			break ;
		if (g_env->cmd == NULL)
			exit_env(g_env);
		parsing(g_env->cmd, g_env);
		if (ft_strlen(g_env->cmd) > 0)
			add_history(g_env->cmd);
	}
	exit_env(g_env);
}
