/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_open_files.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gclement <gclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 13:52:13 by jlaisne           #+#    #+#             */
/*   Updated: 2023/04/07 14:45:05 by gclement         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipes.h"

int	open_fd_in(t_pipex *var, char *filename, t_cmd *lst)
{
	int	count;

	if (filename[0] == '<' || filename[0] == '>')
		return (msg_unexpected_token(filename[0]), 0);
	count = count_type_in_lst(lst, PIPE);
	var->fdin = open(filename, O_RDONLY, 0777);
	if (var->fdin == -1)
	{
		perror("infile");
		if (count == 0)
			exit (1);
	}
	if (var->fdin > -1)
	{
		if (dup2(var->fdin, STDIN_FILENO) < 0)
		{
			perror("dup2");
			exit(EXIT_FAILURE);
		}
	}
	return (1);
}

int	open_fd_out(t_pipex *var, char *filename, int redirect)
{
	if (filename[0] == '<' || filename[0] == '>')
		return (msg_unexpected_token(filename[0]), 0);
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
	return (1);
}

void	search_if_redirect(t_pipex *var, t_cmd *lst, t_minish *env)
{
	size_t	len;
	int		b;

	b = 1;
	while (lst)
	{
		len = ft_strlen(lst->content);
		if (lst->type == REDIRECT)
		{
			if (ft_memcmp("<", lst->content, len) == 0)
				b = open_fd_in(var, lst->next->content, lst);
			else if (ft_memcmp("<<", lst->content, len) == 0)
				create_heredoc(lst, var, env);
			if (ft_memcmp(">", lst->content, len) == 0)
				b = open_fd_out(var, lst->next->content, 0);
			else if (ft_memcmp(">>", lst->content, len) == 0)
				open_fd_out(var, lst->next->content, 1);
		}
		if (b == 0)
			return (free_cmd_list(env->cmd_lst), exit_free(env));
		lst = lst->next;
	}
}


