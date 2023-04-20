/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaisne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 15:13:14 by jlaisne           #+#    #+#             */
/*   Updated: 2023/04/20 14:44:30 by jlaisne          ###   ########.fr       */
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
		g_env->return_status = 130;
		exit_free(g_env);
	}
}

void	signal_fork(int sig)
{
	if (sig == SIGINT)
		exit_free(g_env);
	if (sig == SIGQUIT)
		exit_free(g_env);
}

void	signal_parsing(int sig)
{
	if (sig == SIGINT)
	{
		g_env->return_status = 130;
		printf("\n");
	}
	if (sig == SIGQUIT)
	{
		g_env->return_status = 131;
		printf("Quit (core dumped)\n");
	}
}

void	signal_handler_newl(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_env->return_status = 130;
	}
}
