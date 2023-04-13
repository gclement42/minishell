/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_dup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaisne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 12:22:01 by jlaisne           #+#    #+#             */
/*   Updated: 2023/04/13 10:18:27 by jlaisne          ###   ########.fr       */
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

void	duplicate_fd(int fd, t_pipex *var, t_cmd *lst)
{
	if (fd != 0)
	{
		if (dup2(var->pipefds[fd - 2], STDIN_FILENO) < 0)
		{
			perror("dup2");
			exit(EXIT_FAILURE);
		}
	}
	if (lst_next(lst) != NULL)
	{
		if (dup2(var->pipefds[fd + 1], STDOUT_FILENO) < 0)
		{
			perror("dup2");
			exit(EXIT_FAILURE);
		}
	}
}
