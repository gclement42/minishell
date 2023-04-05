/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaisne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 14:42:09 by jlaisne           #+#    #+#             */
/*   Updated: 2023/04/04 14:26:17 by jlaisne          ###   ########.fr       */
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
		free_tab(tab);
	if (env->env_tab)
		free_2d_array(env->env_tab);
	g_return_status = 127;
	exit_free(env);
}

void	display_error(t_minish *env, char **tab, char *msg)
{
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("\n", 2);
	if (tab)
		free_tab(tab);
	if (env->env_tab)
		free_2d_array(env->env_tab);
	g_return_status = 1;
	exit_free(env);
}

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	free_close(t_pipex *var)
{
	free_tab(var->env_cmd);
	close(STDIN_FILENO);
	close(STDERR_FILENO);
	close(STDOUT_FILENO);
	exit(1);
}
