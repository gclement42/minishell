/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_print.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaisne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 14:02:38 by jlaisne           #+#    #+#             */
/*   Updated: 2023/05/03 10:44:05 by jlaisne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	print_list(t_env **list)
{
	t_env	*temp;

	temp = *list;
	if (!temp)
		return ;
	printf("%s=%s\n", temp->key, temp->content);
	while (temp->next != NULL)
	{
		temp = temp->next;
		printf("%s=%s\n", temp->key, temp->content);
	}
}

void	print_export_list(t_env **list)
{
	t_env	*temp;

	sort_export(list);
	temp = *list;
	if (temp == NULL)
		return ;
	while (temp != NULL)
	{
		if (temp->key && ft_strncmp(temp->key, "_", 2) == 0)
		{
			if (temp->next)
				temp = temp->next;
			else
				return ;
		}
		if (temp->content && ft_strncmp(temp->content, "''", 3) != 0)
			printf("declare -x %s=\"%s\"\n", temp->key, temp->content);
		else
			printf("declare -x %s\n", temp->key);
		temp = temp->next;
	}
}
