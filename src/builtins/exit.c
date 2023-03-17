/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaisne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 14:40:44 by jlaisne           #+#    #+#             */
/*   Updated: 2023/03/17 14:56:32 by jlaisne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	exit_env(void)
{
	ft_putstr_fd("exit\n", 1);
	exit(0);
}

void	exit_parsing(t_cmd *lst)
{
	int	i;

	i = 0;
	while (lst && lst->content[i])
	{
		if (!(lst->content[i] >= '0' && lst->content[i] <= '9'))
		{
			ft_putstr_fd("minishell: exit: ", 2);
			ft_putstr_fd(lst->content, 2);
			ft_putstr_fd(": numeric argument required\n", 2);
			break ;
		}
		i++;
	}
	exit_env();
}