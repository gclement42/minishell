/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaisne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 14:23:08 by gclement          #+#    #+#             */
/*   Updated: 2023/03/01 10:26:40 by jlaisne          ###   ########.fr       */
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
		while(temp_env)
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

void	builtin_cmp(t_minish *var)
{
	if (ft_strncmp(var->cmd, "exit", 5) == 0)
		exit_env(var);
	if (ft_strncmp(var->cmd, "cd ", 2) == 0)
	 	cd(var);
	if (ft_strncmp(var->cmd, "pwd", 3) == 0)
		get_pwd(var);
	if (ft_strncmp(var->cmd, "env", 3) == 0)
	 	get_env(var, &var->env_list);
	if (ft_strncmp(var->cmd, "echo", 4) == 0)
	 	print_echo(0, var->cmd);
	if (ft_strncmp(var->cmd, "export", 6) == 0)
	 	export_env(var);
	if (ft_strncmp(var->cmd, "unset", 5) == 0)
	 	unset_env(var);
}

static void	int_handler(int status)
{
	if (status == SIGINT)
	{
		printf("\n"); // Move to a new line
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();		
	}
	if (status == SIGQUIT)
		return ;
}

int	main(int argc, char **argv, char *envp[])
{
	t_minish	*var;
	
	(void)argv;
	var = malloc(sizeof(t_minish));
	if (!var)
		exit(1);
	signal(SIGINT, &int_handler);
	signal(SIGQUIT, &int_handler);
	if (argc == 1)
	{
		init_struct(var, envp);
		while (1)
		{
			var->cmd = readline(">>");
			if (var->cmd == NULL)
				exit_env(var);
			builtin_cmp(var);
			if (ft_strlen(var->cmd) > 0)
			 	add_history(var->cmd);
			// free(var.cmd);
		}
	}
}
