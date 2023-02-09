/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gclement <gclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 15:05:17 by gclement          #+#    #+#             */
/*   Updated: 2023/02/09 15:26:00 by gclement         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

int	parsing(char *cmd)
{
	char	**split_cmd;
	char	**argexec;

	split_cmd = ft_split(cmd, " ");
	argexec = set_argxec(split_cmd);
	if (ft_)
	return (0);
}

char	**set_argxec(char **cmd)
{
	char	**argxec;
	int		x;

	x = 0;
	while (cmd[x])
		x++;
	argxec = malloc((x + 1) * sizeof(char *));
	if (!argxec)
		exit (EXIT_FAILURE);
	x = 0;
	while (cmd[x])
	{
		argxec[x] = cmd[x];
		x++;
	}
	argxec[x] = NULL;
	return (argxec);
}