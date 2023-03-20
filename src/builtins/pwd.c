/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaisne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 17:19:40 by jlaisne           #+#    #+#             */
/*   Updated: 2023/03/17 14:19:54 by jlaisne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	get_pwd(void)
{
	char *str;

	str = get_cwd();
	if (str == NULL)
		exit (1); // FREE
	printf("%s\n", str);
	return_status = 0;
}

void	pwd_parsing(t_cmd *lst, t_minish *var)
{
	t_cmd	*opt;

	opt = get_node(lst, OPT);
	if (opt)
	{
		ft_putstr_fd("minishell: pwd: ", 2);
		ft_putstr_fd(opt->content, 2);
		ft_putstr_fd(": invalid option\n", 2);
	}
	else
		get_pwd(var);
}
