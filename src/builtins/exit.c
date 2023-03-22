/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaisne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 14:40:44 by jlaisne           #+#    #+#             */
/*   Updated: 2023/03/22 08:50:15 by jlaisne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	exit_env(void)
{
	ft_putstr_fd("exit\n", 1);
		exit(return_status);
}

void	exit_remove_quotes(t_cmd *lst)
{
	
}

void	exit_parsing(t_cmd *lst)
{
	long long	code;

	if (lst->next && lst->next->next)
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
			exit_env();
		}
		else
		{
			code = ft_atoll(lst->next->content);
			return_status = (unsigned char)code;
			exit_env();
		}
	}
	else
		exit_env();
}
