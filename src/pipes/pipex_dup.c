/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_dup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaisne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 12:22:01 by jlaisne           #+#    #+#             */
/*   Updated: 2023/04/19 17:20:19 by jlaisne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipes.h"

void	close_all(void)
{
	int	i;

	i = 0;
	while (i < 1024)
	{
		close(i);
		i++;
	}
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
}

void	duplicate_fd(int fd, t_minish *env, t_cmd *lst)
{
	if (search_if_redirect(env->var, lst, env) == 0)
		return (free_cmd_list(env->cmd_lst), free_pipe_struct(env), \
			exit_free(env));
	if (fd != 0 && env->var->fdin == -1)
		if (dup2(env->var->pipefds[fd - 2], STDIN_FILENO) < 0)
			return (perror("dup2"), exit_free(env));
	if (lst_next(lst) != NULL && env->var->fdout == -1)
		if (dup2(env->var->pipefds[fd + 1], STDOUT_FILENO) < 0)
			return (perror("dup2"), exit_free(env));
	if (lst_next(lst) == NULL && count_type_in_lst(env->cmd_lst, PIPE, -1) != 0
		&& (is_redirect(lst, ">") == 0 || is_redirect(lst, ">>") == 0))
		if (dup2(env->stdout_copy, 1) < 0)
			return (perror("dup2"), exit_free(env));
}
