/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gclement <gclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 14:42:09 by jlaisne           #+#    #+#             */
/*   Updated: 2023/04/24 16:40:00 by gclement         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipes.h"

void	display_error_cmd(t_minish *env, char **tab, char *msg, char *cmd)
{
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("\n", 2);
	if (tab)
		free_2d_array(tab);
	if (env->env_tab)
		free_2d_array(env->env_tab);
	g_return_status = 127;
	exit_free(env);
}

void	display_error_dir(t_minish *env, char **tab, char *msg, char *cmd)
{
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("\n", 2);
	if (tab)
		free_2d_array(tab);
	if (env->env_tab)
		free_2d_array(env->env_tab);
	g_return_status = 126;
	exit_free(env);
}

void	display_error(t_minish *env, char **tab, char *msg)
{
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("\n", 2);
	if (tab)
		free_2d_array(tab);
	if (env->env_tab)
		free_2d_array(env->env_tab);
	if (env->pipex->pipefds)
		free(env->pipex->pipefds);
	g_return_status = 1;
	exit_free(env);
}

void	free_pipe_struct(t_minish *env)
{
	if (env->env_tab)
		free_2d_array(env->env_tab);
	if (env->pipex)
	{
		if (env->pipex->env_cmd)
			free_2d_array(env->pipex->env_cmd);
		if (env->pipex->pipefds)
			free(env->pipex->pipefds);
	}
}
