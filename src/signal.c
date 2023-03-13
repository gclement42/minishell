/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaisne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 15:13:14 by jlaisne           #+#    #+#             */
/*   Updated: 2023/03/13 09:48:58 by jlaisne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();	
		init_sigaction();	
	}
}

void	init_sigaction(void)
{
	struct sigaction	sa;
	struct termios		old_attr;
	struct termios		new_attr;
	
	sa.sa_handler = &signal_handler;
	tcgetattr(STDIN_FILENO, &old_attr);
	new_attr = old_attr;
	new_attr.c_cc[VQUIT] = (cc_t)(intptr_t)SIG_IGN; // or SIG_IGN to ignore
	tcsetattr(STDIN_FILENO, TCSANOW, &new_attr);
	sigaction(SIGQUIT, &sa, NULL);
	sigaction(SIGINT, &sa, NULL);
}