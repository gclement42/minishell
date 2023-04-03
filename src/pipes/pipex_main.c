/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaisne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 10:56:09 by jlaisne           #+#    #+#             */
/*   Updated: 2023/04/03 14:17:09 by jlaisne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipes.h"

static void	execute_child(t_minish *env, t_pipex *var, t_cmd *lst, char **envp)
{
	char	**cmd;

	close_pipes(var);
	if (check_is_builtins(get_node(lst, CMD, PIPE), env) == 1)
	{
		builtins_router(lst, count_type_in_lst(lst, ARG), env);
		exit_free(env);
	}
	else
	{
		cmd = create_arr_exec(lst);
		if (!cmd)
			display_error(env, var->env_cmd, "Command tab not properly allocated");
		exec_command(env, var->env_cmd, cmd, envp);
	}
}

static int	*init_pipes(t_minish *env)
{
	int	i;
	int	*pipefds;

	i = 0;
	pipefds = malloc(sizeof(int) * (2 * env->var->numpipes));
	if (!pipefds)
		exit_free(env);
	while (i < env->var->numpipes)
	{
		if (pipe(pipefds + i * 2) < 0)
		{
			perror("couldn't pipe");
			exit_free(env);
		}
		i++;
	}
	return (pipefds);
}

static void	init_struct_pipex(t_minish *env, char **envp, t_cmd *lst)
{
	env->var->numpipes = count_type_in_lst(lst, PIPE);
	env->var->pipefds = NULL;
	env->var->env_cmd = NULL;
	if (env->var->numpipes > 0)
		env->var->pipefds = init_pipes(env);
	if (envp)
	{
		env->var->env_cmd = get_path(env, envp);
		if (!env->var->env_cmd)
			display_error(env, env->var->env_cmd, "Env tab not properly allocated");
	}
}

static void	child_proc(t_minish *env, t_pipex *var, char **envp, t_cmd *lst)
{
	int		id;
	int		fd;

	fd = 0;
	while (lst)
	{
		if (check_if_unexpected_token(lst) == 0)
			return ;
		id = fork();
		if (id == -1)
			perror("fork: ");
		else if (id == 0)
		{
			init_sigaction(signal_fork);
			duplicate_fd(fd, var, lst);
			close_pipes(var);
			execute_child(env, var, lst, envp);
		}
		fd += 2;
		lst = lst_next(lst);
	}
	close_pipes(env->var);
	wait_id(var);
}

void	pipex(t_minish *env, t_cmd *lst)
{
	env->env_tab = lst_to_tab(&env->env_list);
	if (!env->env_tab)
		exit_free(env);
	if (check_if_unexpected_token(lst) == 0)
		return ;
	if (get_node(lst, CMD, PIPE) != NULL)
	{
		init_sigaction(signal_fork);
		init_struct_pipex(env, env->env_tab, lst);
		child_proc(env, env->var, env->env_tab, get_node(lst, CMD, PIPE));
	}
	free_2d_array(env->env_tab);
}
