/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaisne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 10:09:47 by jlaisne           #+#    #+#             */
/*   Updated: 2023/02/20 10:38:33 by jlaisne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_cwd(void)
{
	char	*cwd;

	if ((cwd = getcwd(NULL, 0)) == NULL)
	{
		if (errno == ERANGE)
			stderr;
		stderr;
	}
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