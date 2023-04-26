/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_arr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gclement <gclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 15:00:58 by gclement          #+#    #+#             */
/*   Updated: 2023/04/24 16:29:33 by gclement         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

const char	**init_bultins_arr(void)
{
	const char	**builtins;

	builtins = malloc(8 * sizeof(char *));
	if (!builtins)
		return (NULL);
	builtins[0] = "echo";
	builtins[1] = "cd";
	builtins[2] = "pwd";
	builtins[3] = "export";
	builtins[4] = "unset";
	builtins[5] = "env";
	builtins[6] = "exit";
	builtins[7] = NULL;
	return (builtins);
}
