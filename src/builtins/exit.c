/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gclement <gclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 14:40:44 by jlaisne           #+#    #+#             */
/*   Updated: 2023/04/03 15:19:02 by gclement         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	exit_env(t_minish *var)
{
	ft_putstr_fd("exit\n", 1);
	exit_free(var);
}

static void	exit_num_arg(t_cmd *lst, t_minish *var)
{
	printf("minishell: exit: %s: numeric argument required\n", \
		lst->next->content);
	return_status = 2;
	exit_env(var);
}

char	*exit_num_parsing(t_cmd *lst, t_minish *var)
{
	t_cmd	*temp;
	char	*arg;
	char	*holder;

	temp = lst->next;
	arg = ft_strdup("");
	if (!arg)
		exit_free(var);
	if (temp->next)
	{
		while (temp)
		{
			holder = arg;
			arg = ft_strjoin(holder, temp->content);
			if (!arg)
				exit_free(var);
			temp = temp->next;
		}
		if (!arg)
			exit_free(var);
		return (arg);
	}
	return (temp->content);
}

void	exit_parsing(t_cmd *lst, t_minish *var)
{
	long long	code;
	char		*arg;

	if (lst->next)
	{
		if (lst->next->type == S_SPACES)
			lst = lst->next;
		arg = exit_num_parsing(lst, var);
		code = ft_atoll(arg);
		if ((lst->next->next && lst->next->next->type == ARG && code == 0) || code == 0)
		{
			if (code == 0 && arg[0] != '0' \
				&& arg[1] != '\0')
				exit_num_arg(lst, var);
			printf("exit\nminishell: exit: too many arguments\n");
			return_status = 1;
			return ;
		}
		else
		{
			return_status = (unsigned char)code;
			exit_env(var);
		}
	}
	exit_env(var);
}
