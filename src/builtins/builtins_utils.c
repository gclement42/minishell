/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaisne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 10:09:47 by jlaisne           #+#    #+#             */
/*   Updated: 2023/02/16 11:01:15 by jlaisne          ###   ########.fr       */
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

static void	add_var_env(t_minish *var, char *key, char *content)
{
	int		len;
	t_env	*temp;
	t_env	*ptr;
	
	len = ft_lstlen(*(var->env_list));
	temp = *(var->env_list);
	ptr = NULL;
	while (len > 2)
	{
		temp = temp->next;
		len--;
	}
	last = temp->next;
	ptr = ft_lstnew_env(key_var[0], key_var[1]);
	temp->next = ptr;
	ptr->next = last;
	last->next = NULL;
}