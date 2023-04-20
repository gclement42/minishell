/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termios.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaisne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 13:34:17 by jlaisne           #+#    #+#             */
/*   Updated: 2023/04/20 10:27:58 by jlaisne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	termios_save(struct termios *termios_save)
{
	if (isatty(STDERR_FILENO) == 0 && errno == ENOTTY)
		errno = 0;
	else if (errno)
		return (1);
	else if (tcgetattr(STDERR_FILENO, termios_save) != 0)
		return (1);
	return (1);
}

int	termios_restore(const struct termios termios_save)
{
	// close (2);
	if (isatty(STDERR_FILENO) == 0 && errno == ENOTTY)
		errno = 0;
	else if (errno)
		return (1);
	else if (tcsetattr(STDERR_FILENO, 0, &termios_save) != 0)
		return (1);
	return (0);
}

int	termios_disable_quit(void)
{
	struct termios	termios_tmp;

	if (isatty(STDERR_FILENO) == 0 && errno == ENOTTY)
	{
		errno = 0;
		return (0);
	}
	else if (errno)
		return (1);
	if (tcgetattr(STDERR_FILENO, &termios_tmp) != 0)
		return (1);
	termios_tmp.c_cc[VQUIT] = (cc_t)(uintptr_t)SIG_IGN;
	if (tcsetattr(STDERR_FILENO, 0, &termios_tmp) != 0)
		return (1);
	return (0);
}

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
