/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaisne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 17:09:12 by jlaisne           #+#    #+#             */
/*   Updated: 2023/02/27 16:32:11 by jlaisne          ###   ########.fr       */
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

// static void	fork_init(t_pipex *var, int arg)
// {
// 	int	index;
// 	int	i;

// 	index = arg - 3;
// 	i = 0;
// 	var->id = malloc(sizeof(int) * index);
// 	if (!var->id)
// 		display_error(var->env_cmd, "Error in malloc");
// 	while (i < index)
// 	{
// 		var->id[i] = fork();
// 		if (var->id[i] == -1)
// 			display_error(var->env_cmd, "Forking unsuccessful");
// 		i++;
// 	}
// }

int	pipex(int arg, char **argv, char **envp)
{
	t_pipex	var;
	int		id;
	int		id_1;

	if (arg == 5)
	{
		init_struct_pipes(&var, argv, envp);
		// fork_init(&var, arg);
		id = fork();
		if (id == -1)
			display_error(var.env_cmd, "Forking unsuccessful");
		if (id == 0)
			child_process(&var, envp);
		id_1 = fork();
		if (id_1 == -1)
			display_error(var.env_cmd, "Forking unsuccessful");
		if (id_1 == 0)
			child_bis_process(&var, envp);
		close_pipe(&var);
		waitpid(id, &var.status, 0);
		waitpid(id_1, &var.status, 0);
	}
	else
		return (ft_putstr_fd("Wrong number of arguments!\n", 2), 3);
	return (free_tab(var.env_cmd), 0);
}
