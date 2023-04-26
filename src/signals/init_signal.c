/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termios.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaisne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 13:34:17 by jlaisne           #+#    #+#             */
/*   Updated: 2023/04/26 10:25:12 by jlaisne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_sigaction(void (*signal_handler)(int))
{
	struct sigaction	sa;

	if (sigemptyset(&sa.sa_mask) == -1)
		return (0);
	sa.sa_flags = SA_RESTART;
	sa.sa_handler = signal_handler;
	if (sigaction(SIGINT, &sa, NULL) == -1)
		return (-1);
	if (sigaction(SIGQUIT, &sa, NULL) == -1)
		return (-1);
	return (0);
}
