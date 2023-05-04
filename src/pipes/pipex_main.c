/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaisne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 10:56:09 by jlaisne           #+#    #+#             */
/*   Updated: 2023/05/04 12:42:08 by jlaisne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipes.h"

static int	*init_pipes(t_minish *env)
{
	int	i;
	int	*pipefds;

	i = 0;
	pipefds = malloc(sizeof(int) * (2 * env->pipex->numpipes));
	if (!pipefds)
		exit_free(env);
	while (i < env->pipex->numpipes)
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
	env->pipex->numpipes = count_type_in_lst(lst, PIPE, -1);
	env->pipex->pipefds = NULL;
	env->pipex->env_cmd = NULL;
	env->pipex->fdin = -1;
	env->pipex->fdout = -1;
	env->hdoc = 0;
	if (env->pipex->numpipes > 0)
		env->pipex->pipefds = init_pipes(env);
	if (envp)
	{
		env->pipex->env_cmd = get_path(env, envp);
		if (!env->pipex->env_cmd)
			return (free_cmd_list(lst), display_error(env, env->pipex->env_cmd, \
						"Env tab not properly allocated"));
	}
}

static void	fork_proc(t_minish *env, int fd, t_cmd *lst)
{
	int		id;

	id = fork();
	if (id == -1)
		perror("fork: ");
	else if (id == 0)
	{
		if (init_sigaction(signal_fork) == -1)
			exit_free(env);
		duplicate_fd(fd, env, lst);
		close_pipes(env->pipex);
		execute_child(env, env->pipex, lst, env->env_tab);
	}
}

static void	child_proc(t_minish *env, t_pipex *pipex, t_cmd *lst)
{
	int		fd;

	fd = 0;
	while (lst)
	{
		if (get_node(lst, CMD, PIPE))
			if (check_if_unexpected_token(get_node(lst, CMD, PIPE), env) == 0)
				return (free_cmd_list(lst), free_pipe_struct(env), \
				exit_free(env));
		fork_proc(env, fd, lst);
		if (!is_here_doc(lst))
		{
			wait_id(pipex);
			env->hdoc = 1;
		}
		fd += 2;
		lst = lst_next(lst);
	}
	close_pipes(pipex);
	close_all();
	if (env->hdoc == 0)
		wait_id(pipex);
}

void	pipex(t_minish *env, t_cmd *lst)
{
	env->env_tab = lst_to_tab(&env->env_list);
	if (!env->env_tab)
		return (free_cmd_list(lst), exit_free(env));
	if (!lst && check_if_unexpected_token(lst, env) == 0)
		return ;
	if (init_sigaction(signal_fork) == -1)
		exit_free(env);
	if (get_node(lst, CMD, -1) != NULL)
	{
		if (init_sigaction(new_signal_here_doc) == -1)
			exit_free(env);
		init_struct_pipex(env, env->env_tab, lst);
		child_proc(env, env->pipex, lst);
	}
	else
		return (free_cmd_list(lst), free_pipe_struct(env), exit_free(env));
	free_pipe_struct(env);
}
