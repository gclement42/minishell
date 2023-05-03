/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaisne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 14:43:19 by jlaisne           #+#    #+#             */
/*   Updated: 2023/05/03 11:02:51 by jlaisne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipes.h"

int	is_redirect(t_cmd *lst, char *redirect)
{
	while (lst && lst->type != PIPE)
	{
		if (ft_memcmp(redirect, lst->content, ft_strlen(lst->content)) == 0)
			return (1);
		lst = lst->next;
	}
	return (0);
}

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

char	**init_empty_tab(char **tab)
{
	tab = malloc(sizeof(char *) * 2);
	if (!tab)
		return (NULL);
	tab[0] = ft_strdup("");
	if (!tab[0])
		return (NULL);
	tab[1] = NULL;
	return (tab);
}

void	wait_id(t_pipex *pipex)
{
	int	i;

	i = 0;
	while (i <= pipex->numpipes)
	{
		wait(&pipex->status);
		if (WIFSIGNALED(pipex->status) && (WTERMSIG(pipex->status) == SIGINT
				|| WTERMSIG(pipex->status) == SIGQUIT))
		{
			if (WTERMSIG(pipex->status) == SIGQUIT)
				g_return_status = 131;
			else if (WTERMSIG(pipex->status) == SIGINT)
				g_return_status = 130;
		}
		else if (WEXITSTATUS(pipex->status))
			g_return_status = WEXITSTATUS(pipex->status);
		else
			g_return_status = 0;
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
