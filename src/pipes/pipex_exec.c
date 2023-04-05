/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaisne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 17:15:40 by jlaisne           #+#    #+#             */
/*   Updated: 2023/04/05 13:57:54 by jlaisne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipes.h"

char	**get_path(t_minish *env, char **envp)
{
	char	*path;
	char	**tab;
	int		i;

	i = 0;
	while (envp[i])
	{
		if (ft_strnstr(envp[i], "PATH=", 5))
		{
			path = ft_strdup(ft_strnstr_path(envp[i], \
				"PATH=", ft_strlen(envp[i])));
			if (!path)
				return (NULL);
			tab = ft_split(path, ':');
			free(path);
			if (!tab)
				return (NULL);
			join_slash(env, tab);
			return (tab);
		}
		i++;
	}
	return (envp);
}

static void	execution(t_minish *env, char *path, char **cmd, char **envp)
{
	free(env->var->pipefds);
	if (execve(path, cmd, envp) == -1)
	{
		perror("exec");
		free(path);
		free_tab(env->var->env_cmd);
		exit_free(env);
	}
}

static void	check_cmd(t_minish *env, char **cmd, char **envp, char **path)
{
	if (cmd[0][0] == '\0')
	{
		free_tab(path);
		display_error_cmd(env, cmd, "command not found", cmd[0]);
	}
	if (cmd[0][0] == '.' && cmd[0][1] == '/' && access(cmd[0], X_OK) == -1)
	{
		free_tab(path);
		display_error_cmd(env, cmd, "command not found", cmd[0]);
	}
	if (access(cmd[0], X_OK) != -1)
		execution(env, cmd[0], cmd, envp);
}

void	exec_command(t_minish *env, char **path, char **cmd, char *envp[])
{
	int		i;
	char	*exe;

	i = 0;
	check_cmd(env, cmd, envp, path);
	while (path[i])
	{
		exe = ft_strjoin(path[i], cmd[0]);
		if (!exe)
			display_error(env, path, "execution line not properly allocated");
		if (access(exe, X_OK) == -1)
		{
			if (!path[i + 1])
			{
				free_tab(path);
				free(exe);
				display_error_cmd(env, cmd, "command not found", cmd[0]);
			}
			free(exe);
			i++;
		}
		else
			execution(env, exe, cmd, envp);
	}
}
