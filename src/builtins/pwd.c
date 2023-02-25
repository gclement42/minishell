/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaisne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 17:19:40 by jlaisne           #+#    #+#             */
/*   Updated: 2023/02/25 09:53:35 by jlaisne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	get_pwd(t_minish *var)
{
	t_env	*temp;
	char	*str;

	temp = var->env_list;
	if (temp)
	{
		var->pwd = NULL;
		if (check_key(&(var->env_list), "PWD") == 0)
		{
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
		else
		{
			str = get_cwd();
			printf("%s\n", str);
		}
	}
}
