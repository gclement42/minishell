/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaisne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 14:19:51 by jlaisne           #+#    #+#             */
/*   Updated: 2023/02/14 15:04:39 by jlaisne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	echo_no_backslash(char *echo_line)
{
	int	i;

	i = 0;
	while(echo_line[i])
	{
		ft_putchar_fd(echo_line[i], 1);
		i++;
	}
}

void	echo_backslash(char *echo_line)
{
	ft_putstr_fd(echo_line, 1);
	ft_putchar_fd('\n', 1);
}

void	print_echo(int option, char *echo_line)
{
	if (option == 0)
		echo_backslash(echo_line);
	else
		echo_no_backslash(echo_line);
}