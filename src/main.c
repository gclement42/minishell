/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaisne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 14:23:08 by gclement          #+#    #+#             */
/*   Updated: 2023/02/08 10:11:14 by jlaisne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int main(int argc, char **argv, char *envp[])
{
    char    *cmd;
    
    (void)argc;
    (void)argv;
    (void)envp;
    while (1)
    {
        cmd = readline("$> ");
        if (ft_strncmp(cmd, "exit", 5))
            break ;
    }
    return (0);
}