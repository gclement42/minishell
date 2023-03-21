/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_open_files.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaisne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 13:52:13 by jlaisne           #+#    #+#             */
/*   Updated: 2023/03/21 10:43:39 by jlaisne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipes.h"

void	open_fd_in(t_pipex *var, char *filename, t_cmd *lst)
{
	int	count;

	count = count_type_in_lst(lst, PIPE);
	var->fdin = open(filename, O_RDONLY, 0777);
	if (var->fdin == -1)
	{
		perror("infile");
		if (count == 0)
			exit (1);
	}
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
		exit(1);
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
				open_fd_in(var, lst->next->content, lst);
			else if (ft_memcmp("<<", lst->content, ft_strlen(lst->content)) == 0)
				create_heredoc(lst, pipe_fd, var);
			if (ft_memcmp(">", lst->content, ft_strlen(lst->content)) == 0)
				open_fd_out(var, lst->next->content, 0);
			else if (ft_memcmp(">>", lst->content, ft_strlen(lst->content)) == 0)
				open_fd_out(var, lst->next->content, 1);
		}
		lst = lst->next;
	}
}

void	create_heredoc(t_cmd *lst, int pipe_fd[2], t_pipex *var)
{
	char	*line;
	pid_t	pid;
	
	(void)lst;
	if (pipe(pipe_fd) < 0)
	{
		perror("pipe");
		exit (1);
	}
	pid = fork();
	if (pid < 0)
		return (perror("fork"), exit(1));
	if (pid == 0)
	{
		close(pipe_fd[0]);
		init_sigaction(signal_here_doc);
		line = readline(">");
		while (ft_strlen(line) == 0 || ft_strncmp(lst->next->content, line, ft_strlen(line)) != 0)
		{
			if (write(pipe_fd[1], line, ft_strlen(line) + 1) < 0)
				return (perror("write"));
			if (write(pipe_fd[1], "\n", 1) < 0)
				perror("write");
			free (line);
			line = readline(">");
		}
		exit (0);
	}
	wait (&var->status);
	if (WEXITSTATUS(var->status))
		return_status = WEXITSTATUS(var->status);
	close(pipe_fd[1]);
	if(dup2(pipe_fd[0], STDIN_FILENO) < 0)
	{
		perror("dup2");
		exit(EXIT_FAILURE);
	}
	if (return_status == 130)
		exit(return_status);
}