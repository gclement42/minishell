/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaisne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 14:43:19 by jlaisne           #+#    #+#             */
/*   Updated: 2023/04/03 14:17:33 by jlaisne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipes.h"

void	join_slash(t_minish *env, char **path)
{
	int		i;
	char	*temp;

	i = 0;
	while (path[i])
	{
		temp = ft_strdup(path[i]);
		if (!temp)
			display_error(env, path, "Error in  malloc");
		free(path[i]);
		path[i] = ft_strjoin(temp, "/");
		if (!path[i])
			display_error(env, path, "Error in  malloc");
		free(temp);
		i++;
	}
}

void	wait_id(t_pipex *var)
{
	int	i;

	i = 0;
	while (i <= var->numpipes)
	{
		wait(&var->status);
		if (WEXITSTATUS(var->status))
			return_status = WEXITSTATUS(var->status); // WEXITSTATUS(var->status);
		else
			return_status = 0;
		i++;
	}
}

t_cmd	*lst_next(t_cmd *lst)
{
	if (get_node(lst, PIPE, -1) != NULL)
	{
		lst = get_node(lst, PIPE, -1);
		if (lst && lst->next)
			lst = lst->next;
		else
			lst = NULL;
	}
	else
		lst = NULL;
	return (lst);
}
