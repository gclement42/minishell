/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_parsing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gclement <gclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 10:37:47 by gclement          #+#    #+#             */
/*   Updated: 2023/02/23 11:14:23 by gclement         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	builtins_parsing(char **arg, int argc)
// {
// 	if (ft_memcmp(arg[0], "cd", 2) == 0)
// 	{
// 		if (argc > 2)
// 			return (ft_putstr_fd("minishell: cd : too many arguments\n", 2));
// 		else if (argc == 1)
// 			cd("~");
// 		else
// 			cd(arg[1]);
// 	}
// 	if (ft_memcmp(arg[0], "pwd", 3) == 0)
// 		ft_printf("pwd");
// 	if (ft_memcmp(arg[0], "env", 3) == 0)
// 	{
// 		if (argc > 1)
// 			return (ft_putstr_fd("minishell: env : too many arguments\n", 2));
// 		ft_printf("env");
// 	}
// 	// if (ft_memcmp(arg[0], "unset", 5) == 0)
// 	// 	unset_parsing(arg);
// 	// if (ft_memcmp(arg[0], "export", 6) == 0)
// 	// 	export_parsing(arg);
// 	if (ft_memcmp(arg[0], "exit", 4) == 0)
// 		exit_parsing(arg);
// 	// if (ft_memcmp(arg[0], "echo", 4) == 0)
// 	// 	echo_parsing(arg);
// }

// void	exit_parsing(char **arg)
// {
// 	printf("%d", ft_atoi(arg[1]));
// }
