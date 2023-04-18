/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaisne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 14:43:19 by jlaisne           #+#    #+#             */
/*   Updated: 2023/04/17 14:14:01 by jlaisne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipes.h"

int	is_redirect(t_cmd *lst)
{
	if (ft_memcmp("<<", lst->content, ft_strlen(lst->content)) == 0)
		return (0);
	if (ft_memcmp(">", lst->content, ft_strlen(lst->content)) == 0)
		return (0);
	if (ft_memcmp(">>", lst->content, ft_strlen(lst->content)) == 0)
		return (0);
	if (ft_memcmp("<", lst->content, ft_strlen(lst->content)) == 0)
		return (0);
	return (1);
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

void	wait_id(t_pipex *var)
{
	int	i;

	i = 0;
	while (i <= var->numpipes)
	{
		wait(&var->status);
		if (WEXITSTATUS(var->status))
			g_return_status = WEXITSTATUS(var->status);
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
