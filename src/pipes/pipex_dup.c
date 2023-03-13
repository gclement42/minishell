/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_dup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaisne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 12:22:01 by jlaisne           #+#    #+#             */
/*   Updated: 2023/03/13 12:29:47 by jlaisne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipes.h"

// static void	duplicate_redir(int count, int fd, t_pipex *var, t_cmd *lst)
// {
// 	// if (var->fdin && fd != 0)
// 	// {
// 	// 	if (dup2(var->pipefds[fd - 2], STDIN_FILENO) < 0)
// 	// 	{
// 	// 		perror("dup2");
// 	// 		exit(EXIT_FAILURE);
// 	// 	}
// 	// }
// 	// if (var->fdout)
// 	// {
// 	// 	if (lst_next(lst) != NULL && count + 1 < var->numpipes)
// 	// 	{
// 	// 		if (dup2(var->pipefds[fd + 1], STDOUT_FILENO) < 0)
// 	// 		{
// 	// 			perror("dup2");
// 	// 			exit(EXIT_FAILURE);
// 	// 		}
// 	// 	}	
// 	// }	
// }

void	duplicate_fd(int count, int fd, t_pipex *var, t_cmd *lst)
{
	(void)count;
	if (fd != 0)
	{
		if (dup2(var->pipefds[fd - 2], STDIN_FILENO) < 0)
		{
			perror(" dup2");
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
	// else
	// 	duplicate_redir(count, fd, var, lst);
}
