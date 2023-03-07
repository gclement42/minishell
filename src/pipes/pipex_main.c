/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaisne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 10:56:09 by jlaisne           #+#    #+#             */
/*   Updated: 2023/03/07 15:13:28 by jlaisne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipes.h"

int	*init_pipes(t_pipex *var)
{
	int	i;
	int	*pipefds;

	i = 0;
	pipefds = malloc(sizeof(int) * (2 * var->numpipes));
	if (!pipefds)
		exit (1); //FREE
	while (i < var->numpipes)
	{
		if (pipe(pipefds + i * 2) < 0)
		{
			perror("couldn't pipe");
				exit(EXIT_FAILURE);
		}
		i++;
	}
	return (pipefds);
}

void	close_pipes(t_pipex *var)
{
	int	i;

	i = 0;
	while (i < var->numpipes * 2)
	{
		close(var->pipefds[i]);
		i++;
	}
}

void	init_struct_pipex(t_minish *env, char **envp, t_cmd *lst)
{
	env->var->numpipes = count_type_in_lst(lst, PIPE);
	if (env->var->numpipes > 0)
		env->var->pipefds = init_pipes(env->var);
	if (envp)
	{
		env->var->env_cmd = get_path(envp);
		if (!env->var->env_cmd)
			display_error(env->var->env_cmd, "Env tab not properly allocated");
	}
}

void	child_proc(t_minish *env, t_pipex *var, char **envp, t_cmd *lst)
{
	int		id;
	int		fd;
	char	**cmd;
	int		count;

	fd = 0;
	count = 0;
	while (count <= var->numpipes)
	{
		id = fork();
		if (id == -1)
			perror("fork: ");
		if (id == 0)
		{
			if (var->numpipes != 0 && fd != 0 && fd != 2 * var->numpipes) // command != 0 for in
			{
				if (dup2(var->pipefds[fd - 2], STDIN_FILENO) < 0)
				{
					perror(" dup2");
					exit(EXIT_FAILURE);
				}
			}
			if (var->numpipes != 0 && count + 1 < var->numpipes) // command != command max - 1 for out 
			{
				if (dup2(var->pipefds[fd + 1], STDOUT_FILENO) < 0)
				{
					perror("dup2");
					exit(EXIT_FAILURE);
				}
			}
			close_pipes(var);
			if (check_is_builtins(get_node(lst, CMD), env) == 1)
			{
				builtins_router(lst, count_type_in_lst(lst, ARG), env);
				break ;
			}
			cmd = create_arr_exec(lst);
			if (!cmd)
				display_error(var->env_cmd, "Command tab not properly allocated");
			exec_command(var, var->env_cmd, cmd, envp);
		}
		count++;
		fd += 2;
	}
}

void	pipex(t_minish *env, t_cmd *lst)
{
	int		i;

	env->var = malloc(sizeof(t_pipex));
	if (!env->var)
		exit (1); //FREE
	init_struct_pipex(env, env->env_tab, lst);
	child_proc(env, env->var, env->env_tab, lst);
	close_pipes(env->var);
	i = 0;
	while (i < env->var->numpipes + 1)
	{
		wait(&env->var->status);
		i++;
	}
}
