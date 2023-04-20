/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gclement <gclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 13:29:08 by gclement          #+#    #+#             */
/*   Updated: 2023/04/20 14:36:56 by gclement         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_here_doc(t_cmd *lst)
{
	if (ft_memcmp("<<", lst->content, ft_strlen(lst->content)) == 0)
		return (0);
	return (1);
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
			line = check_if_replace_var(line, env, 0);
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

static void	dup_heredoc(t_pipex *pipex, int pipe_fd[2], t_cmd *lst)
{
	wait (&pipex->status);
	if (WEXITSTATUS(pipex->status))
		g_env->return_status = WEXITSTATUS(pipex->status);
	close(pipe_fd[1]);
	if (g_env->return_status == 130)
		exit(g_env->return_status);
	if (!lst->next->next || ft_memcmp(lst->content, \
		lst->next->next->content, ft_strlen(lst->content)) != 0)
	{
		if (dup2(pipe_fd[0], STDIN_FILENO) < 0)
		{
			perror("dup2");
			exit (EXIT_SUCCESS);
		}
	}
}

int	create_heredoc(t_cmd *lst, t_pipex *pipex, t_minish *env)
{
	pid_t	pid;
	int		pipe_fd[2];

	if (lst->next->content[0] == '<'
		|| lst->next->content[0] == '>'
		|| lst->next->content[0] == '|')
		return (msg_unexpected_token(lst->next->content[0]), 0);
	if (pipe(pipe_fd) < 0)
		return (perror("pipe"), exit (g_env->return_status), 0);
	pid = fork();
	if (pid < 0)
		return (perror("fork"), exit(g_env->return_status), 0);
	if (pid == 0)
	{
		close(pipe_fd[0]);
		if (init_sigaction(signal_here_doc) == -1)
			exit_free(env);
		if (!lst->next->next || ft_memcmp(lst->content,
				lst->next->next->content, ft_strlen(lst->content)) != 0)
			write_in_heredoc(pipe_fd[1], lst->next, 1, env);
		else
			write_in_heredoc(pipe_fd[1], lst->next, 0, env);
		return (free_cmd_list(env->cmd_lst), free_pipe_struct(env), exit_free(env), 1);
	}
	return (env->pipex->fdin = 0, dup_heredoc(pipex, pipe_fd, lst), 1);
}
