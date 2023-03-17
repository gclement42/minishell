/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termios.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaisne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 13:34:17 by jlaisne           #+#    #+#             */
/*   Updated: 2023/03/14 14:10:28 by jlaisne          ###   ########.fr       */
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