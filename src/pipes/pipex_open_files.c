/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_open_files.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaisne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 13:52:13 by jlaisne           #+#    #+#             */
/*   Updated: 2023/03/09 15:23:49 by jlaisne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipes.h"

void	open_fd_in(t_pipex *var, char *filename)
{
	var->fdin = open(filename, O_RDONLY, 0777);
	if (var->fdin == -1)
		perror("infile");
	if (dup2(var->fdin, STDIN_FILENO) < 0)
	{
		perror("dup2");
		exit(EXIT_FAILURE);
	}
}

void	open_fd_out(t_pipex *var, char *filename, int redirect)
{
	if (redirect == 0)
		var->fdout = open(filename, O_RDWR | O_CREAT | O_TRUNC, 0644);
	else
		var->fdout = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (var->fdout == -1)
	{
		perror("outfile");
		close(var->fdout);
		free_close(var);
		exit(0);
	}
	if (dup2(var->fdout, STDOUT_FILENO) < 0)
	{
		perror("dup2");
		exit(EXIT_FAILURE);
	}
}
