/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaisne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 18:14:31 by gclement          #+#    #+#             */
/*   Updated: 2023/04/13 15:42:35 by jlaisne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_is_good_arg_cd(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] == '.')
		i++;
	if (i == 2)
		return (1);
	else
		return (0);
}

void	cd_parsing(t_cmd *lst, int argc, t_minish *var)
{
	int	i;

	i = 0;
	if (argc > 1 && lst->content[0] != '<')
		return (ft_putstr_fd("minishell: cd : too many arguments\n", 2));
	else if (argc == 0 || lst->content[0] == '\0' || \
		(lst && ft_strchr(lst->content, '~') != 0) || lst->content[0] == '<')
	{
		if ((lst && lst->next && check_is_good_arg_cd(lst->next->content) == 1) || lst->content[0] == '\0')
		{
			cd(var, NULL);
			return ;
		}
		while (argc != 0 && lst->content[i])
		{
			if (lst->content[i] != '~')
				return (ft_putstr_fd("errr", 2)); //quasi sur que c'est pas le bon msg d'erreur
			i++;
		}
		if (cd(var, NULL) == -1)
			g_return_status = 1;
	}
	else if (cd(var, lst->content) == -1)
		g_return_status = 1;
}
