/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gclement <gclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 15:05:17 by gclement          #+#    #+#             */
/*   Updated: 2023/02/14 10:19:39 by gclement         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtins_parsing(char **arg)
{
	int	count;

	count = count_nb_arg(arg);
	if (ft_memcmp(arg[0], "cd", 2) == 0)
	{
		if (count > 2)
			free_and_exit("minishell: cd : too many arguments", arg);
		else if (count == 1)
			cd("~");
		else
			cd(arg[1]);
	}
	if (ft_memcmp(arg[0], "pwd", 3) == 0)
		ft_printf("pwd");
	if (ft_memcmp(arg[0], "env", 3) == 0)
	{
		if (count > 1)
			free_and_exit("minishell: cd : too many arguments", arg);
		ft_printf("env");
	}
}

char	**parsing(char *cmd, t_minish env)
{
	char	**split_cmd;
	char	**arg_exec;

	split_cmd = ft_split(cmd, ' ');
	if (!split_cmd)
		exit (EXIT_FAILURE);
	arg_exec = set_argxec(split_cmd);
	if (!arg_exec)
		free_2d_array(arg_exec);
	if (check_is_builtins(split_cmd[0], env) == 1)
		builtins_parsing(arg_exec);
	return (arg_exec);
}

