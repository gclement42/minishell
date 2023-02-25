/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaisne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 17:15:40 by jlaisne           #+#    #+#             */
/*   Updated: 2023/02/25 10:35:58 by jlaisne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipes.h"

char	**get_path(char *envp[])
{
	char	*path;
	char	**tab;
	int		i;

	i = 0;
	while (envp[i])
	{
		path = ft_strnstr(envp[i], "PATH=", 5);
		if (path)
		{
			path = ft_strdup(ft_strnstr_path(envp[i], \
				"PATH=", ft_strlen(envp[i])));
			break ;
		}
		free(path);
		i++;
	}
	tab = ft_split(path, ':');
	free(path);
	if (!tab)
		exit(EXIT_FAILURE);
	join_slash(tab);
	return (tab);
}

static void	check_cmd(char **cmd, char **envp, char **env)
{
	if (!cmd[0])
	{
		free_tab(env);
		display_error_cmd(cmd, "permission denied: ", cmd[0]);
	}
	if (cmd[0][0] == '.' && cmd[0][1] == '/' && access(cmd[0], X_OK) == -1)
	{
		free_tab(env);
		display_error_cmd(cmd, "command not found", cmd[0]);
	}
	if (access(cmd[0], X_OK) != -1)
	{
		execve(cmd[0], cmd, envp);
		perror(">");
	}		
}

static void	execution(t_pipex *var, char *exec, char **cmd, char **envp)
{
	if (execve(exec, cmd, envp) == -1)
	{
		close_pipe(var);
		free_tab(var->env_cmd);
		free(exec);
		perror("exec");
	}
}

void	exec_command(t_pipex *var, char **env, char **cmd, char *envp[])
{
	int		i;
	char	*exe;

	i = 0;
	check_cmd(cmd, envp, env);
	while (env[i])
	{
		exe = ft_strjoin(env[i], cmd[0]);
		if (!exe)
			display_error(env, "execution line not properly allocated");
		if (access(exe, X_OK) == -1)
		{
			if (!env[i + 1])
			{
				free_tab(env);
				free(exe);
				display_error_cmd(cmd, "command not found", cmd[0]);
			}
			free(exe);
			i++;
		}
		else
			execution(var, exe, cmd, envp);
	}
}
