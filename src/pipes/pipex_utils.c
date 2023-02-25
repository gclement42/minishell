/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaisne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 14:43:19 by jlaisne           #+#    #+#             */
/*   Updated: 2023/02/25 10:38:24 by jlaisne          ###   ########.fr       */
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

void	open_fd(t_pipex *var, char **argv)
{
	var->fd1 = open(argv[1], O_RDONLY, 0777);
	if (var->fd1 == -1)
	{
		perror("infile");
		// free_close(var);
		// exit(0);
	}
	var->fd2 = open(var->arg[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (var->fd2 == -1)
	{
		perror("outfile");
		close(var->fd1);
		free_close(var);
		exit(0);
	}
}
