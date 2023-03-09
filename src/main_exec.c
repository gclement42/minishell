/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaisne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 14:23:08 by gclement          #+#    #+#             */
/*   Updated: 2023/03/09 15:00:40 by jlaisne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_shlvl(t_minish *var, t_env **env_l, t_env **exp_l)
{
	t_env	*temp_env;
	t_env	*temp_exp;
	char	*str_lvl;

	temp_env = *env_l;
	temp_exp = *exp_l;
	if (check_key(&temp_env, "SHLVL") == 0)
	{
		while (temp_env)
		{
			if (ft_strnstr(temp_env->key, "SHLVL", 6))
			{
				var->lvl = ft_atoi(temp_env->content);
				var->lvl++;
				str_lvl = ft_itoa(var->lvl);
				if (!str_lvl)
					exit(1); //FREE
				modify_var(&temp_env, "SHLVL", str_lvl);
				modify_var(&temp_exp, "SHLVL", str_lvl);
				free(str_lvl);
			}
			temp_env = temp_env->next;
		}
	}
}

void	init_struct(t_minish *var, char **envp)
{
	var->env_list = NULL;
	var->exp_list = NULL;
	set_env(envp, &(var->env_list), &(var->exp_list));
	modify_var(&(var->env_list), "_", "/usr/bin/env");
	set_shlvl(var, &(var->env_list), &(var->exp_list));
}

// void	signal_handler(int status)
// {
// 	if (status == SIGINT)
// 	{
// 		printf("\n"); // Move to a new line
// 		rl_on_new_line();
// 		rl_replace_line("", 0);
// 		rl_redisplay();		
// 	}
// 	if (status == SIGQUIT)
// 	{
// 		return ;
// 	}
// }

int	main(int argc, char **argv, char *envp[])
{
	t_minish	*var;

	var = malloc(sizeof(t_minish));
	if (!var)
		exit(1);
	// signal(SIGINT, &int_handler);
	// signal(SIGQUIT, &int_handler);
	(void)argv;
	var->builtins = init_bultins_arr();
	//signal_handler;
	if (argc == 1)
	{
		init_struct(var, envp);
		while (1)
		{
			//signal_handler;
			var->cmd = readline(">>");
			if (var->cmd == NULL)
				exit_env(var);
			parsing(var->cmd, var);
			if (ft_strlen(var->cmd) > 0)
				add_history(var->cmd);
		}
	}
}
