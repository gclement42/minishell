/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaisne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 17:09:12 by jlaisne           #+#    #+#             */
/*   Updated: 2023/02/25 10:38:17 by jlaisne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipes.h"

static void	init_struct_pipes(t_pipex *var, char **argv, char **envp)
{
	if (envp)
	{
		var->env_cmd = get_path(envp);
		if (!var->env_cmd)
			display_error(var->env_cmd, "Env tab not properly allocated");
	}
	else
		exit(1);
	var->arg = argv;
	open_fd(var, argv);
	if (pipe(var->file) == -1)
	{
		close_pipe(var);
		display_error(var->env_cmd, "Pipe returned an error");
	}
}

static void	child_process(t_pipex *var, char **envp)
{
	char	**cmd;

	close(var->fd2);
	close(var->file[0]);
	if (dup2(var->fd1, STDIN_FILENO) == -1)
	{
		close(var->file[1]);
		free_close(var);
	}
	if (dup2(var->file[1], STDOUT_FILENO) == -1)
	{
		close(var->fd1);
		free_close(var);
	}
	cmd = get_command(var->arg[2], var->env_cmd);
	if (!cmd)
		display_error(var->env_cmd, "Command tab not properly allocated");
	exec_command(var, var->env_cmd, cmd, envp);
	exit(0);
}

static void	child_bis_process(t_pipex *var, char **envp)
{
	char	**cmd;

	close(var->fd1);
	close(var->file[1]);
	if (dup2(var->file[0], STDIN_FILENO) == -1)
	{
		close(var->fd2);
		free_close(var);
	}
	if (dup2(var->fd2, STDOUT_FILENO) == -1)
	{
		close(var->file[0]);
		free_close(var);
	}
	cmd = get_command(var->arg[3], var->env_cmd);
	if (!cmd)
		display_error(var->env_cmd, "Command tab not properly allocated");
	exec_command(var, var->env_cmd, cmd, envp);
	exit(0);
}

int	pipex(int arg, char **argv, char **envp)
{
	int		id;
	int		id_2;
	t_pipex	var;

	if (arg == 5)
	{
		init_struct_pipes(&var, argv, envp);
		id = fork();
		if (id == -1)
			display_error(var.env_cmd, "Forking unsuccessful");
		if (id == 0)
			child_process(&var, envp);
		id_2 = fork();
		if (id_2 == -1)
			display_error(var.env_cmd, "Forking unsuccessful");
		if (id_2 == 0)
			child_bis_process(&var, envp);
		close_pipe(&var);
		waitpid(id, &var.status, 0);
		waitpid(id_2, &var.status, 0);
	}
	else
		return (ft_putstr_fd("Wrong number of arguments!\n", 2), 3);
	return (free_tab(var.env_cmd), 0);
}
