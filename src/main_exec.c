/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaisne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 14:23:08 by gclement          #+#    #+#             */
/*   Updated: 2023/04/24 15:14:39 by jlaisne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

unsigned char	g_return_status = 0;

static void	init_struct(t_minish *env, char **envp)
{
	env->env_list = NULL;
	env->exp_list = NULL;
	env->oldpwd = NULL;
	env->env_tab = NULL;
	env->builtins = NULL;
	env->cd_path = NULL;
	env->pipex = NULL;
	env->cmd_lst = NULL;
	env->cmd = NULL;
	env->stdout_copy = -1;
	env->builtins = init_bultins_arr();
	termios_save(&env->orig_ter);
	set_env(env, envp, &(env->env_list), &(env->exp_list));
	modify_var(env, &(env->env_list), "_", "/usr/bin/env");
	set_shlvl(env, &(env->env_list), &(env->exp_list));
	env->pipex = malloc(sizeof(t_pipex));
	if (!env->pipex)
		exit_env(env);
}

int	main(int argc, char **argv, char *envp[])
{
	t_minish		*env;

	env = malloc(sizeof(t_minish));
	if (!env)
		exit(1);
	(void)argv;
	(void)argc;
	init_struct(env, envp);
	while (1)
	{
		if (init_sigaction(signal_handler_newl) == -1)
			exit_free(env);
		if (termios_disable_quit() == 1)
			break ;
		env->cmd = readline("\033[1;31m minishell $> \033[0m");
		if (termios_restore(env->orig_ter) == 1)
			break ;
		if (env->cmd == NULL)
			exit_env(env);
		parsing(env->cmd, env);
		if (ft_strlen(env->cmd) > 0)
			add_history(env->cmd);
	}
	exit_env(env);
}
