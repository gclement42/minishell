/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gclement <gclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 10:09:47 by jlaisne           #+#    #+#             */
/*   Updated: 2023/04/03 18:41:27 by gclement         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

char	*get_cwd(void)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (cwd == NULL)
		return (free(cwd), NULL);
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

void	modify_var(t_minish *var, t_env **list, char *key, char *str)
{
	t_env	*temp;
	int		len;

	len = ft_strlen(key);
	temp = *list;
	if (!str)
		return ;
	while (temp)
	{
		if (ft_strncmp(key, temp->key, len + 1) == 0)
		{
			free(temp->content);
			temp->content = ft_strdup(str);
			if (!temp->content)
				exit_free(var);
		}
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
