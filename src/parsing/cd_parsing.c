/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaisne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 18:14:31 by gclement          #+#    #+#             */
/*   Updated: 2023/05/03 16:12:02 by jlaisne          ###   ########.fr       */
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

static int	check_if_opt(t_cmd *lst, int *argc)
{
	t_cmd	*opt;

	opt = get_node(lst, OPT, PIPE);
	if (opt && !ft_memcmp(opt->content, "-", ft_strlen(opt->content)))
	{
		opt->type = ARG;
		*argc += 1;
	}
	else if (opt)
	{
		ft_putstr_fd("cd:", 2);
		ft_putstr_fd(opt->content, 2);
		ft_putstr_fd(": invalid option\n", 2);
		return (0);
	}
	return (1);
}

void	cd_parsing(t_cmd *lst, int argc, t_minish *var)
{
	check_if_opt(lst, &argc);
	if (get_node(lst, ARG, PIPE))
		lst = get_node(lst, ARG, PIPE);
	if (argc > 1 && lst->content[0] != '<')
		return (ft_putstr_fd("minishell: cd : too many arguments\n", 2));
	else if (argc == 0 || lst->content[0] == '\0' || \
		(lst && ft_strchr(lst->content, '~') != 0) || lst->content[0] == '<')
	{
		if (argc == 0)
		{
			cd(var, NULL);
			return ;
		}
	}
	cd(var, lst->content);
}
