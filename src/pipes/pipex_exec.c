/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gclement <gclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 17:15:40 by jlaisne           #+#    #+#             */
/*   Updated: 2023/04/13 11:12:47 by gclement         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipes.h"

char	**get_path(t_minish *env, char **envp)
{
	char	*path;
	char	**tab;
	t_env	*temp;

	(void)envp;
	tab = NULL;
	if (check_key(&env->env_list, "PATH") == 0)
	{
		temp = get_key_node(env->env_list, "PATH");
		path = ft_strdup(temp->content);
		if (!path)
			return (NULL);
		tab = ft_split(path, ':');
		free(path);
		if (!tab)
			return (NULL);
		join_slash(env, tab);
		return (tab);
	}
	tab = init_empty_tab(tab);
	if (!tab)
		return (NULL);
	return (tab);
}

static void	execution(t_minish *env, char *path, char **cmd, char **envp)
{
	free(env->var->pipefds);
	if (execve(path, cmd, envp) == -1)
	{
		perror("exec");
		free(path);
		free_2d_array(env->var->env_cmd);
		exit_free(env);
	}
}

static void	check_cmd(t_minish *env, char **cmd, char **envp, char **path)
{
	if (path[0][0] == '\0')
		display_error_cmd(env, cmd, "No such file or directory", cmd[0]);
	if (cmd[0][0] == '\0')
	{
		free_2d_array(path);
		display_error_cmd(env, cmd, "command not found", "''");
	}
	if (cmd[0][0] == '.' && cmd[0][1] == '/' && access(cmd[0], X_OK) == -1)
	{
		free_2d_array(path);
		display_error_cmd(env, cmd, "No such file or directory", cmd[0]);
	}
	if (cmd[0][0] == '/')
	{
		free_2d_array(path);
		if (opendir(cmd[0]))
			display_error_dir(env, cmd, "Is a directory", cmd[0]);
		else if (access(cmd[0], X_OK) != -1)
			execution(env, cmd[0], cmd, envp);
		else
			display_error_cmd(env, cmd, "No such file or directory", cmd[0]);
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
				free(exe);
				free(env->var->pipefds);
				free_2d_array(path);
				display_error_cmd(env, cmd, "command not found", cmd[0]);
			}
			free(exe);
			i++;
		}
		else
			execution(env, exe, cmd, envp);
	}
}
