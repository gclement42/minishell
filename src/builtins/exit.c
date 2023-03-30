/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaisne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 14:40:44 by jlaisne           #+#    #+#             */
/*   Updated: 2023/03/30 15:46:37 by jlaisne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	exit_env(t_minish *var)
{
	ft_putstr_fd("exit\n", 1);
	exit_free(var);
	exit(return_status);
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
		while (temp && ft_atoll(temp->content) != 0)
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
		arg = exit_num_parsing(lst, var);
		code = ft_atoll(arg);
		printf("%lld\n", code);
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
