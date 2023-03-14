/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaisne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 10:09:47 by jlaisne           #+#    #+#             */
/*   Updated: 2023/03/14 10:23:25 by jlaisne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

char	*get_cwd(void)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (errno)
		exit (1); //FREE
	return (cwd);
}

void	add_var_env(t_env **lst, char *key, char *content)
{
	int		len;
	t_env	*temp;
	t_env	*ptr;
	t_env	*last;

	len = ft_lstlen(*lst);
	temp = *lst;
	ptr = NULL;
	while (len > 2)
	{
		temp = temp->next;
		len--;
	}
	last = temp->next;
	ptr = ft_lstnew_env(key, content);
	temp->next = ptr;
	ptr->next = last;
	last->next = NULL;
}

int	check_key(t_env **lst, char *key)
{
	t_env			*temp;
	unsigned int	len;

	temp = *lst;
	len = ft_strlen(key);
	while (temp)
	{
		if (ft_strncmp(key, temp->key, len) == 0)
			return (0);
		temp = temp->next;
	}
	return (1);
}

void	modify_var(t_env **list, char *key, char *str)
{
	t_env	*temp;
	int		len;

	len = ft_strlen(key);
	temp = *list;
	while (temp)
	{
		if (ft_strncmp(key, temp->key, len + 1) == 0)
			temp->content = ft_strdup(str);
		temp = temp->next;
	}
}

int	get_shlvl(t_env **list)
{
	t_env	*temp;
	int		res;

	temp = *list;
	res = 0;
	if (check_key(list, "SHLVL") == 1)
	{
		while (temp)
		{
			if (ft_strncmp("SHLVL", temp->key, 6) == 0)
			{
				res = ft_atoi(temp->content);
				return (res);
			}
			temp = temp->next;
		}
	}
	return (0);
}
