/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gclement <gclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 14:40:44 by jlaisne           #+#    #+#             */
/*   Updated: 2023/03/14 11:15:37 by gclement         ###   ########.fr       */
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

void	exit_parsing(t_minish *var, t_cmd *lst)
{
	int	i;

	i = 0;
	while (lst && lst->content[i])
	{
		if (!(lst->content[i] >= '0' && lst->content[i] <= '9'))
		{
			ft_putstr_fd("minishell: exit: ", 2);
			ft_putstr_fd(lst->content, 2);
			ft_putstr_fd(": numeric argument required\n", 2);
			break ;
		}
		i++;
	}
	exit_env(var);
}