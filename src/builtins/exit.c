/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gclement <gclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 14:40:44 by jlaisne           #+#    #+#             */
/*   Updated: 2023/03/22 09:04:06 by gclement         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	exit_env(t_minish *var)
{
	exit_free(var);
	ft_putstr_fd("exit\n", 1);
		exit(return_status);
}

// void	exit_remove_quotes(t_cmd *lst)
// {
		
// }

void	exit_parsing(t_cmd *lst, t_minish *var)
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
			exit_env(var);
		}
		else
		{
			code = ft_atoll(lst->next->content);
			return_status = (unsigned char)code;
			exit_env(var);
		}
	}
	exit_env(var);
}
