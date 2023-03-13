/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gclement <gclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 10:56:09 by jlaisne           #+#    #+#             */
/*   Updated: 2023/03/13 11:32:09 by gclement         ###   ########.fr       */
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

void    child_proc(t_minish *env, t_pipex *var, char **envp, t_cmd *lst)
{
	int		id;
	int		fd;
	char	**cmd;
	int		count;

	fd = 0;
	count = 0;
	while (lst)
	{
		id = fork();
		if (id == -1)
			perror("fork: ");
		else if (id == 0)
		{
			duplicate_fd(count, fd, var, lst);
			close_pipes(var);
			if (check_is_builtins(get_node(lst, CMD), env) == 1)
      		{
				builtins_router(lst, count_type_in_lst(lst, ARG), env);
				exit(0);
			}
			else
			{
				cmd = create_arr_exec(lst);
				if (!cmd)
					display_error(var->env_cmd, "Command tab not properly allocated");
				exec_command(var, var->env_cmd, cmd, envp);
			}
		}
		count++;
		fd += 2;
		lst = lst_next(lst);
	}
	close_pipes(env->var);
	wait_id(var);
}

void	pipex(t_minish *env, t_cmd *lst)
{
	if (get_node(lst, ARG) != NULL)
	{
		init_struct_pipex(env, env->env_tab, lst);
		child_proc(env, env->var, env->env_tab, get_node(lst, CMD));
	}
}
