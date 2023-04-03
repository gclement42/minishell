/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gclement <gclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 17:15:40 by jlaisne           #+#    #+#             */
/*   Updated: 2023/03/31 14:39:26 by gclement         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipes.h"

char	**get_path(char **envp)
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
			join_slash(tab);
			return (tab);
		}
		i++;
	}
	return (envp);
}

static void	execution(t_pipex *var, char *path, char **cmd, char **envp)
{
	// DEAL WITH EXEC COMMAND ERRORS
	if (execve(path, cmd, envp) == -1)
	{
		perror("exec");
		// close_pipes(var);
		free_tab(var->env_cmd);
		exit (1);
	//	free(path);
	}
}

static void	check_cmd(t_pipex *var, char **cmd, char **envp, char **env)
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
		execution(var, cmd[0], cmd, envp);
}

void	exec_command(t_pipex *var, char **env, char **cmd, char *envp[])
{
	int		i;
	char	*exe;

	i = 0;
	check_cmd(var, cmd, envp, env);
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
