/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaisne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 14:40:44 by jlaisne           #+#    #+#             */
/*   Updated: 2023/03/20 11:18:06 by jlaisne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	exit_env(void)
{
	ft_putstr_fd("exit\n", 1);
	exit(return_status);
}

void	exit_parsing(t_cmd *lst)
{
	long long	code;

	if (lst->next->next)
	{
		printf("minishell: exit: too many arguments\n");
		return_status = 1;
		return ;
	}
	if (lst->next)
	{
		if (ft_atoll(lst->next->content) == 0 && lst->next->content[0] != '0' \
			&& lst->next->content[1] != '\0')
		{
			printf("minishell: exit: %s: numeric argument required\n", \
				lst->next->content);
			return_status = 2;
		}
		else
		{
			code = ft_atoll(lst->next->content);
			return_status = (unsigned char)code;
		}
	}
	exit_env();
}
