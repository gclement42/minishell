/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaisne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 17:19:40 by jlaisne           #+#    #+#             */
/*   Updated: 2023/02/15 14:20:28 by jlaisne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_pwd(t_minish *var)
{
	t_env	*temp;

	temp = *(var->env_list);
	if (temp)
	{
		var->pwd = NULL;
		while (temp->next)
		{
			if (ft_strnstr(temp->key, "PWD", 4))
				break;
			temp = temp->next;
		}
		var->pwd = ft_strdup(temp->content);
		printf("%s\n", var->pwd);
		free(var->pwd);
	}
}
