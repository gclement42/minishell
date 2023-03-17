/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_open_files.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaisne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 13:52:13 by jlaisne           #+#    #+#             */
/*   Updated: 2023/03/14 14:35:35 by jlaisne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipes.h"

void	open_fd_in(t_pipex *var, char *filename)
{
	var->fdin = open(filename, O_RDONLY, 0777);
	if (var->fdin == -1)
		perror("infile");
	if (var->fdin  > -1)
	{
		if (dup2(var->fdin, STDIN_FILENO) < 0)
		{
			perror("dup2");
			exit(EXIT_FAILURE);
		}
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
	else
	{
		if (dup2(var->fdout, STDOUT_FILENO) < 0)
		{
			perror("dup2");
			exit(EXIT_FAILURE);
		}
	}
}

void	search_if_redirect(t_pipex *var, t_cmd *lst, int pipe_fd[2])
{
	while (lst)
	{
		if (lst->type == REDIRECT)
		{
			if (ft_memcmp("<", lst->content, ft_strlen(lst->content)) == 0)
				open_fd_in(var, lst->next->content);
			else if (ft_memcmp("<<", lst->content, ft_strlen(lst->content)) == 0)
				create_heredoc(lst, pipe_fd);
			if (ft_memcmp(">", lst->content, ft_strlen(lst->content)) == 0)
				open_fd_out(var, lst->next->content, 0);
			else if (ft_memcmp(">>", lst->content, ft_strlen(lst->content)) == 0)
				open_fd_out(var, lst->next->content, 1);
		}
		lst = lst->next;
	}
}