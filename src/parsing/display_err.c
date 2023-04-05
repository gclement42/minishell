/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_err.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaisne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 19:29:53 by gclement          #+#    #+#             */
/*   Updated: 2023/04/04 14:26:17 by jlaisne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	msg_invalid_opt(char *str, char *cmd)
{
	int		i;

	i = -1;
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": ", 2);
	while (++i < 2)
		ft_putchar_fd(str[i], 2);
	ft_putstr_fd(": invalid option ", 2);
	ft_putstr_fd("\n", 2);
	g_return_status = 1;
}

void	msg_unexpected_token(char token)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	ft_putchar_fd(token, 2);
	ft_putstr_fd("'\n", 2);
}
