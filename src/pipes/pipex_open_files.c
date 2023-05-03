/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_open_files.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gclement <gclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 13:52:13 by jlaisne           #+#    #+#             */
/*   Updated: 2023/05/03 13:32:45 by gclement         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipes.h"

int	open_fd_in(t_minish *env, char *filename, t_marks mark, t_cmd *lst)
{
	int	count;

	if (mark == SPACES
		&& (filename[0] == '<' || filename[0] == '>' || filename[0] == '|'))
		return (msg_unexpected_token(filename[0]), 0);
	count = count_type_in_lst(lst, PIPE, -1);
	env->pipex->fdin = open(filename, O_RDONLY, 0777);
	if (env->pipex->fdin == -1)
	{
		perror(filename);
		if (count == 0)
			return (0);
	}
	if (env->pipex->fdin > -1)
	{
		if (dup2(env->pipex->fdin, STDIN_FILENO) < 0)
		{
			perror("dup2");
			return (0);
		}
	}
	return (1);
}

int	open_fd_out(t_minish *env, char *filename, t_marks mark, int redirect)
{
	if (mark == SPACES
		&& (filename[0] == '<' || filename[0] == '>' || filename[0] == '|'))
		return (msg_unexpected_token(filename[0]), 0);
	if (redirect == 0)
		env->pipex->fdout = open(filename, O_RDWR | O_CREAT | O_TRUNC, 0644);
	else
		env->pipex->fdout = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (env->pipex->fdout == -1)
	{
		perror("outfile");
		return (0);
	}
	else
	{
		if (dup2(env->pipex->fdout, STDOUT_FILENO) < 0)
		{
			perror("dup2");
			return (0);
		}
	}
	return (1);
}

int	search_if_redirect(t_cmd *lst, t_minish *env)
{
	size_t	len;
	int		b;

	b = 1;
	while (lst && lst->type != PIPE)
	{
		len = ft_strlen(lst->content);
		if (lst->type == REDIRECT)
		{
			if (!lst->next)
				return (msg_unexpected_token(0), 0);
			if (!ft_memcmp("<", lst->content, len) && lst->next->content)
				b = open_fd_in(env, lst->next->content, lst->next->marks, lst);
			else if (!ft_memcmp("<<", lst->content, len) && lst->next->content)
				b = create_heredoc(lst, env);
			if (!ft_memcmp(">", lst->content, len) && lst->next->content)
				b = open_fd_out(env, lst->next->content, lst->next->marks, 0);
			else if (!ft_memcmp(">>", lst->content, len) && lst->next->content)
				b = open_fd_out(env, lst->next->content, lst->next->marks, 1);
		}
		if (b == 0)
			return (g_return_status = 1, 0);
		lst = lst->next;
	}
	return (1);
}
