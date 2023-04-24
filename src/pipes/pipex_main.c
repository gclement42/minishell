/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gclement <gclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 10:56:09 by jlaisne           #+#    #+#             */
/*   Updated: 2023/04/24 16:47:07 by gclement         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipes.h"

void	execute_child(t_minish *env, t_pipex *pipex, t_cmd *lst, char **envp)
{
	char	**cmd;

	close_pipes(pipex);
	if (check_is_builtins(get_node(lst, CMD, PIPE), env) == 1)
	{
		free_pipe_struct(env);
		builtins_router(get_node(lst, CMD, PIPE), \
			count_type_in_lst(lst, ARG, PIPE), env);
		if (env->cmd_lst)
			free_cmd_list(env->cmd_lst);
		exit_free(env);
	}
	else
	{
		cmd = create_arr_exec(lst);
		if (!cmd)
			return (free_cmd_list(env->cmd_lst), display_error(env, pipex->env_cmd, \
						"Command tab not properly allocated"));
		free_cmd_list(env->cmd_lst);
		exec_command(env, pipex->env_cmd, cmd, envp);
	}
}

int	*init_pipes(t_minish *env)
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

void	init_struct_pipex(t_minish *env, char **envp, t_cmd *lst)
{
	env->pipex->numpipes = count_type_in_lst(lst, PIPE, -1);
	env->pipex->pipefds = NULL;
	env->pipex->env_cmd = NULL;
	env->pipex->fdin = -1;
	env->pipex->fdout = -1;
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

void	child_proc(t_minish *env, t_pipex *pipex, char **envp, t_cmd *lst)
{
	int		id;
	int		fd;

	fd = 0;
	while (lst)
	{
		if (check_if_unexpected_token(lst, env) == 0)
			return ;
		id = fork();
		if (id == -1)
			perror("fork: ");
		else if (id == 0)
		{
			if (init_sigaction(signal_fork) == -1)
				exit_free(env);
			duplicate_fd(fd, env, lst);
			close_pipes(pipex);
			execute_child(env, pipex, lst, envp);
		}
		if (is_here_doc(lst) == 0)
			wait(NULL);
		fd += 2;
		lst = lst_next(lst);
	}
	close_pipes(pipex);
	close_all();
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
		init_struct_pipex(env, env->env_tab, lst);
		child_proc(env, env->pipex, env->env_tab, lst);
	}
	free_pipe_struct(env);
}
