/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gclement <gclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 10:56:09 by jlaisne           #+#    #+#             */
/*   Updated: 2023/03/07 11:07:44 by gclement         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipes.h"

static int	*init_pipes(t_pipex *var)
{
	int	i;
	int	*pipefds;

	i = 0;
	pipefds = malloc(sizeof(int) * (2 * var->numpipes));
	while (i < var->numpipes)
	{
		if (pipe(pipefds + i * 2) < 0)
		{
			perror("couldn't pipe");
				exit(EXIT_FAILURE);
		}
		i++;
	}
	return (pipefds);
}

void	close_pipes(t_pipex *var)
{
	int	i;

	i = 0;
	while (i < var->numpipes * 2)
	{
		close(var->pipefds[i]);
		i++;
	}
	free(var->pipefds);
}

static void	init_struct_pipex(t_pipex *var, char **argv, char **envp, int argc)
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
	var->numpipes = argc;
	var->pipefds = init_pipes(var);
}

static void	child_proc(t_pipex *var, char **envp)
{
	int		id;
	int		fd;
	int		command;
	char	**cmd;

	command = 1;
	fd = 0;
	while (var->arg[command] && command < 5)
	{
		id = fork();
		if (id == -1)
			perror("fork: ");
		if (id == 0)
		{
			if (fd != 0 && fd != 2 * var->numpipes) // command != 0 for in
			{
				if (dup2(var->pipefds[fd - 2], 0) < 0)
				{
					perror(" dup2");
					exit(EXIT_FAILURE);
				}
			}
			if (var->arg[command + 1] && command != 4) // command != command max - 1 for out 
			{
				if (dup2(var->pipefds[fd + 1], 1) < 0)
				{
					perror("dup2");
					exit(EXIT_FAILURE);
				}
			}
			close_pipes(var);
			cmd = get_command(var->arg[command], var->env_cmd);
			if (!cmd)
				display_error(var->env_cmd, "Command tab not properly allocated");
			exec_command(var, var->env_cmd, cmd, envp);
		}
		command++;
		fd += 2;
	}
}

void	pipex(int argc, char **arg_exec, char **envp, t_pipex var)
{
	int		i;

	if (!arg_exec)
		return ;
	init_struct_pipex(&var, arg_exec, envp, argc);
	child_proc(&var, envp);
	close_pipes(&var);
	i = 0;
	while (i < var.numpipes + 1)
	{
		wait(&var.status);
		i++;
	}
}
