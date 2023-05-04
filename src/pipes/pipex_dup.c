/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_dup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaisne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 12:22:01 by jlaisne           #+#    #+#             */
/*   Updated: 2023/05/04 12:06:55 by jlaisne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipes.h"

void	close_all(void)
{
	int	i;

	i = 3;
	while (i < 1024)
	{
		close(i);
		i++;
	}
}

void	close_pipes(t_pipex *pipex)
{
	int	i;

	i = 0;
	while (i < pipex->numpipes * 2)
	{
		close(pipex->pipefds[i]);
		i++;
	}
}

void	duplicate_fd(int fd, t_minish *env, t_cmd *lst)
{
	if (search_if_redirect(lst, env) == 0)
		return (free_cmd_list(env->cmd_lst), free_pipe_struct(env), \
			exit_free(env));
	if (fd != 0 && env->pipex->fdin == -1)
		if (dup2(env->pipex->pipefds[fd - 2], STDIN_FILENO) < 0)
			return (perror("dup2"), exit_free(env));
	if (lst_next(lst) != NULL && env->pipex->fdout == -1)
		if (dup2(env->pipex->pipefds[fd + 1], STDOUT_FILENO) < 0)
			return (perror("dup2"), exit_free(env));
	if (lst_next(lst) == NULL && count_type_in_lst(env->cmd_lst, PIPE, -1) != 0
		&& (!is_redirect(lst, ">>")))
		if (dup2(env->stdout_copy, 1) < 0)
			return (perror("dup2"), \
			free_cmd_list(env->cmd_lst), exit_free(env));
}
