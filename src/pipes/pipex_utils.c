/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaisne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 14:43:19 by jlaisne           #+#    #+#             */
/*   Updated: 2023/03/07 13:36:39 by jlaisne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipes.h"

void	join_slash(char **env)
{
	int		i;
	char	*temp;

	i = 0;
	while (env[i])
	{
		temp = ft_strdup(env[i]);
		if (!temp)
			display_error(env, "Error in  malloc");
		free(env[i]);
		env[i] = ft_strjoin(temp, "/");
		if (!env[i])
			display_error(env, "Error in  malloc");
		free(temp);
		i++;
	}
}

char	**get_command(char *arg, char **env)
{
	char	**cmd;

	(void) arg;
	cmd = ft_split(arg, ' ');
	if (!cmd)
		display_error(env, "Error in malloc");
	return (cmd);
}
