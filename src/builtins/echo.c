/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaisne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 14:19:51 by jlaisne           #+#    #+#             */
/*   Updated: 2023/04/05 13:26:37 by jlaisne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	echo_no_backslash(char *echo_line)
{
	int	i;

	i = 0;
	if (!echo_line)
		return ;
	while (echo_line[i])
	{
		ft_putchar_fd(echo_line[i], 2);
		i++;
	}
}

void	echo_backslash(char *echo_line)
{
	ft_putstr_fd(echo_line, 2);
	ft_putchar_fd('\n', 2);
}

void	print_echo(int option, char *echo_line)
{
	if (option == 0)
		echo_backslash(echo_line);
	else
		echo_no_backslash(echo_line);
	g_return_status = 0;
}
