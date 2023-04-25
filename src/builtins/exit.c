/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaisne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 14:40:44 by jlaisne           #+#    #+#             */
/*   Updated: 2023/04/25 14:20:30 by jlaisne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	exit_env(t_minish *var)
{
	ft_putstr_fd("exit\n", 1);
	exit_free(var);
}

static void	exit_arg(t_minish *var, char **exit_args, long long code)
{
	if (code == 0 && (exit_args[0][0] == '-' || exit_args[0][0] == '+') \
		&& exit_args[0][1] == '0' && exit_args[0][2] == '\0')
		return ;
	if (code == 0 && (exit_args[0][0] != 0 && exit_args[0][1] != '\0'))
	{
		printf("minishell: exit: %s: numeric argument required\n", exit_args[0]);
		g_return_status = 2;
		free_2d_array(exit_args);
		free_cmd_list(var->cmd_lst);
		exit_env(var);
	}
	if (exit_args[1])
	{
		free_2d_array(exit_args);
		printf("exit\nminishell: exit: too many arguments\n");
		g_return_status = 1;
	}
	else
		g_return_status = 0;
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
	if (temp)
	{
		while (temp)
		{
			holder = arg;
			arg = ft_strjoin(holder, temp->content);
			if (!arg)
				exit_free(var);
			free(holder);
			temp = temp->next;
		}
		return (arg);
	}
	return (free(arg), temp->content);
}

void	exit_parsing(t_cmd *lst, t_minish *var)
{
	long long	code;
	char		*arg;
	char		**exit_args;

	if (lst && lst->next)
	{
		if (lst->next->type == S_SPACES)
			lst = lst->next;
		arg = exit_num_parsing(lst, var);
		exit_args = ft_split(arg, ' ');
		free(arg);
		if (!exit_args)
			exit_free(var);
		code = ft_atoll(exit_args[0]);
		exit_arg(var, exit_args, code);
		if (g_return_status == 1)
			return ;
		g_return_status = (unsigned char)code;
		free_2d_array(exit_args);
	}
	if (var->cmd_lst)
		free_cmd_list(var->cmd_lst);
	exit_env(var);
}
