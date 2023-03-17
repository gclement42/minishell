/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaisne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 15:13:14 by jlaisne           #+#    #+#             */
/*   Updated: 2023/03/17 14:47:36 by jlaisne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	new_signal_here_doc(int sig)
{
	(void)sig;
}

void	signal_here_doc(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		return_status = 130;
		exit (return_status);
	}
}

void	signal_fork(int sig)
{
	if (sig == SIGINT)
		exit (130);
	if (sig == SIGQUIT)
		exit (131);
}

void	signal_parsing(int sig)
{
	if (sig == SIGINT)
	{
		return_status = 130;
		printf("\n");
	}
	if (sig == SIGQUIT)
	{
		return_status = 131;
		printf("Quit (core dumped)\n");
	}
}

void signal_handler_newl(int sig)
{
	if (sig == SIGINT) 
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		return_status = 130;
	}
}

void	init_sigaction(void (*signal_handler)(int))
{
	struct sigaction	sa;

	if (sigemptyset(&sa.sa_mask) == -1)
		return ;
	sa.sa_flags = SA_RESTART;
	sa.sa_handler = signal_handler;
	if (sigaction(SIGINT, &sa, NULL) == -1)
		exit (1); //FREE
	if (sigaction(SIGQUIT, &sa, NULL) == -1)
		exit (1); //FREE
}
