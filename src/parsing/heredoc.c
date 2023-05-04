/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaisne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 13:29:08 by gclement          #+#    #+#             */
/*   Updated: 2023/05/04 12:52:37 by jlaisne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_here_doc(t_cmd *lst)
{
	if (!ft_memcmp("<<", lst->content, 2) && ft_strlen(lst->content) == 2)
		return (0);
	return (1);
}

void	write_in_heredoc(int fd, t_cmd *eof, int bools, t_minish *env)
{
	char	*line;

	line = readline(">");
	if (!line || str_isascii(line) == 0)
		return (ft_printf("minishell: warning: here-document delimited by end-of-file \
		(wanted %s)\n", eof->content), free_cmd_list(env->cmd_lst), \
			exit_free(env));
	while (!ft_strlen(line) || ft_strncmp(eof->content, line, ft_strlen(line))
		|| ft_strlen(line) != ft_strlen(eof->content))
	{
		if (eof->marks == SPACES)
			line = check_if_replace_var_in_str(line, '\0', env);
		if (bools == 1)
		{
			if (write(fd, line, ft_strlen(line)) < 0)
				return (perror("write"));
			if (write(fd, "\n", 1) < 0)
				perror("write");
		}
		free(line);
		line = readline(">");
		if (!line || str_isascii(line) == 0)
			return (ft_printf("minishell: warning: here-document delimited by end-of-file \
			(wanted %s)\n", eof->content), free_cmd_list(env->cmd_lst), \
				exit_free(env));
	}
}

void	dup_heredoc(t_minish *env, int pipe_fd[2], t_cmd *lst)
{
	wait (&env->pipex->status);
	if (WIFSIGNALED(env->pipex->status)
		&& WTERMSIG(env->pipex->status) == SIGINT)
	{
		if (WTERMSIG(env->pipex->status) == SIGINT)
			g_return_status = 130;
	}
	if (WEXITSTATUS(env->pipex->status))
		g_return_status = WEXITSTATUS(env->pipex->status);
	close(pipe_fd[1]);
	if (!lst->next->next || ft_memcmp(lst->content, \
		lst->next->next->content, ft_strlen(lst->content)) != 0)
	{
		if (dup2(pipe_fd[0], STDIN_FILENO) < 0)
		{
			perror("dup2");
			exit (EXIT_SUCCESS);
		}
	}
	close(pipe_fd[0]);
}

void	exec_here_doc(int pipe_fd[2], t_minish *env, t_cmd *lst)
{
	int	len;

	len = 0;
	if (lst->content)
		len = ft_strlen(lst->content);
	close(pipe_fd[0]);
	if (init_sigaction(new_signal_here_doc) == -1)
		exit_free(env);
	if (!lst->next->next || ft_memcmp(lst->content,
			lst->next->next->content, len) != 0)
		write_in_heredoc(pipe_fd[1], lst->next, 1, env);
	else
		write_in_heredoc(pipe_fd[1], lst->next, 0, env);
}

int	create_heredoc(t_cmd *lst, t_minish *env)
{
	pid_t	pid;
	int		pipe_fd[2];

	if (lst->next->marks == SPACES
		&& (lst->next->content[0] == '<'
			|| lst->next->content[0] == '>' || lst->next->content[0] == '|'))
		return (msg_unexpected_token(lst->next->content[0]), 0);
	if (pipe(pipe_fd) < 0)
		return (perror("pipe"), exit(g_return_status), 0);
	if (signal_ignore() != 0)
		return (free_cmd_list(env->cmd_lst), \
			free_pipe_struct(env), exit_free(env), 1);
	pid = fork();
	if (pid < 0)
		return (perror("fork"), exit(g_return_status), 0);
	if (pid == 0)
	{
		exec_here_doc(pipe_fd, env, lst);
		return (free_cmd_list(env->cmd_lst), \
			free_pipe_struct(env), exit_free(env), 1);
	}
	return (env->pipex->fdin = 0, dup_heredoc(env, pipe_fd, lst), 1);
}
