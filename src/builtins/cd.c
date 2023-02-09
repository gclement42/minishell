/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gclement <gclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 10:51:57 by gclement          #+#    #+#             */
/*   Updated: 2023/02/09 14:16:03 by gclement         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

int	cd(char *arg)
{
	if (chdir(arg) == -1)
	{
		printf("cd: no such file or directory: %s", arg);
		return (-1);
	}
	else
		return (1);
}
