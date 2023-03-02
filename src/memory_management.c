/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_management.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaisne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 17:55:16 by gclement          #+#    #+#             */
/*   Updated: 2023/02/27 13:31:25 by jlaisne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*free_2d_array(char **ptr)
{
	int	i;

	i = 0;
	while (ptr[i])
	{
		free(ptr[i]);
		i++;
	}
	free(ptr);
	return (NULL);
}

void	free_and_exit(char *msg, char **arg)
{
	ft_putstr_fd(msg, 2);
	if (arg)
		free_2d_array(arg);
	exit (EXIT_SUCCESS);
}

void	exit_free(t_minish *var)
{
	if (var->env_list)
		free_list(var->env_list);
	if (var->exp_list)
		free_list(var->exp_list);
	free(var);
	exit (1);
}