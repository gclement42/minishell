/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaisne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 15:13:14 by jlaisne           #+#    #+#             */
/*   Updated: 2023/05/03 10:48:05 by jlaisne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	signal_ignore(void)
{
	if (signal(SIGINT, SIG_IGN) == SIG_ERR)
		return (1);
	if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
		return (1);
	return (0);
}

void	new_signal_here_doc(int sig)
{
	(void)sig;
}

void	signal_fork(int sig)
{
	if (sig == SIGINT)
		exit(130);
	if (sig == SIGQUIT)
		exit(131);
}

void	signal_parsing(int sig)
{
	if (sig == SIGINT)
	{
		g_return_status = 130;
		ft_printf("\n");
	}
	if (sig == SIGQUIT)
	{
		g_return_status = 131;
		ft_printf("Quit (core dumped)\n");
	}
}

void	signal_handler_newl(int sig)
{
	if (sig == SIGINT)
	{
		ft_printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_return_status = 130;
	}
}
