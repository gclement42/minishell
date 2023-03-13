/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaisne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 14:40:44 by jlaisne           #+#    #+#             */
/*   Updated: 2023/03/09 16:01:08 by jlaisne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	exit_env(t_minish *var)
{
	struct termios old_attr;
	struct sigaction sa;

	sa.sa_handler = SIG_DFL;
	sigaction(SIGINT, &sa, NULL);
    sigaction(SIGQUIT, &sa, NULL);
	if (var->cmd)
	{
		sigaction(SIGINT, &sa, NULL);
		sigaction(SIGQUIT, &sa, NULL);
		tcgetattr(STDIN_FILENO, &old_attr);
		old_attr.c_cc[VQUIT] = (cc_t)(intptr_t)SIG_DFL;
		tcsetattr(STDIN_FILENO, TCSANOW, &old_attr);
		ft_putstr_fd("exit\n", 1);
	}
	else
	{
		sigaction(SIGINT, &sa, NULL);
		sigaction(SIGQUIT, &sa, NULL);
		tcgetattr(STDIN_FILENO, &old_attr);
		old_attr.c_cc[VQUIT] = (cc_t)(intptr_t)SIG_DFL;
		tcsetattr(STDIN_FILENO, TCSANOW, &old_attr);
		ft_putstr_fd("\n", 1);
	}
	exit(0);
}
