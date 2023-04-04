/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_open_files.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaisne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 13:52:13 by jlaisne           #+#    #+#             */
/*   Updated: 2023/04/04 09:56:09 by jlaisne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipes.h"

void	open_fd_in(t_pipex *var, char *filename, t_cmd *lst)
{
	int	count;

	if (filename[0] == '<' || filename[0] == '>')
		return (msg_unexpected_token(filename[0]));
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
	if (filename[0] == '<' || filename[0] == '>')
		return (msg_unexpected_token(filename[0]));
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

void	search_if_redirect(t_pipex *var, t_cmd *lst, t_minish *env)
{
	size_t	len;

	while (lst)
	{
		len = ft_strlen(lst->content);
		if (lst->type == REDIRECT)
		{
			if (ft_memcmp("<", lst->content, len) == 0)
				open_fd_in(var, lst->next->content, lst);
			else if (ft_memcmp("<<", lst->content, len) == 0)
				create_heredoc(lst, var, env);
			if (ft_memcmp(">", lst->content, len) == 0)
				open_fd_out(var, lst->next->content, 0);
			else if (ft_memcmp(">>", lst->content, len) == 0)
				open_fd_out(var, lst->next->content, 1);
		}
		lst = lst->next;
	}
}

static void	write_in_heredoc(int fd, t_cmd *eof, int bools, t_minish *env)
{
	char	*line;

	line = readline(">");
	if (!line)
		printf("minishell: warning: here-document delimited by end-of-file \
		(wanted %s)\n", eof->content);
	while (!ft_strlen(line) || ft_strncmp(eof->content, line, ft_strlen(line))
		|| ft_strlen(line) != ft_strlen(eof->content))
	{
		if (eof->marks != QUOTE)
			line = replace_variable(line, env, 0, 0);
		if (bools == 1)
		{
			if (write(fd, line, ft_strlen(line) + 1) < 0)
				return (perror("write"));
			if (write(fd, "\n", 1) < 0)
				perror("write");
		}
		free (line);
		line = readline(">");
		if (!line)
			printf("minishell: warning: here-document delimited by end-of-file \
			(wanted %s)\n", eof->content);
	}
}

void    create_heredoc(t_cmd *lst, t_pipex *var, t_minish *env)
{
	pid_t	pid;
	int		pipe_fd[2];

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
		if (!lst->next->next || ft_memcmp(lst->content, lst->next->next->content, ft_strlen(lst->content)) != 0)
			write_in_heredoc(pipe_fd[1], lst->next, 1, env);
		else
			write_in_heredoc(pipe_fd[1], lst->next, 0, env);
		exit (0);
	}
	wait (&var->status);
	if (WEXITSTATUS(var->status))
		return_status = WEXITSTATUS(var->status);
	close(pipe_fd[1]);
	if (return_status == 130)
		exit(return_status);
	if (!lst->next->next || ft_memcmp(lst->content, lst->next->next->content, ft_strlen(lst->content)) != 0)
	{
		if (dup2(pipe_fd[0], STDIN_FILENO) < 0)
		{
			perror("dup2");
			exit (EXIT_SUCCESS);
		}
	}
}
