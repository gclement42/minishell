/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaisne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 14:23:08 by gclement          #+#    #+#             */
/*   Updated: 2023/05/03 11:21:14 by jlaisne          ###   ########.fr       */
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
	if (!env->builtins)
		return (free(env), exit(EXIT_FAILURE));
	set_env(env, envp, &(env->env_list), &(env->exp_list));
	modify_var(env, &(env->env_list), "_", "/usr/bin/env");
	set_shlvl(env, &(env->env_list), &(env->exp_list));
	env->pipex = malloc(sizeof(t_pipex));
	if (!env->pipex)
		exit_env(env);
	env->pipex->cmd = NULL;
	env->pipex->env_cmd = NULL;
	env->pipex->pipefds = NULL;
}

int	main(int argc, char **argv, char *envp[])
{
	t_minish		*env;

	env = malloc(sizeof(t_minish));
	if (!env)
		exit(EXIT_FAILURE);
	(void)argv;
	(void)argc;
	init_struct(env, envp);
	while (1)
	{
		if (init_sigaction(signal_handler_newl) == -1)
			exit_free(env);
		if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
			exit_free(env);
		env->cmd = readline("minishell $> ");
		if (env->cmd == NULL || str_isascii(env->cmd) == 0)
			exit_env(env);
		add_history(env->cmd);
		parsing(env->cmd, env);
	}
	exit_env(env);
}
