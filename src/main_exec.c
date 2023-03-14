/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaisne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 14:23:08 by gclement          #+#    #+#             */
/*   Updated: 2023/03/14 10:36:44 by jlaisne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

unsigned char	g_return_value = 0;

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
	t_minish	*var;

	var = malloc(sizeof(t_minish));
	if (!var)
		exit(1);
	(void)argv;
	var->builtins = init_bultins_arr();
	init_sigaction();
	if (argc == 1)
	{
		init_struct(var, envp);
		init_sigaction();
		while (1)
		{
			while (1)
			{
				init_sigaction();
				var->cmd = readline(">>");
				if (var->cmd == NULL)
					exit_env(var);
				parsing(var->cmd, var);
				if (ft_strlen(var->cmd) > 0)
					add_history(var->cmd);
			}
			rl_clear_history();
		}
	}
}
