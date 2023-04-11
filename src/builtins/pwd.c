/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaisne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 17:19:40 by jlaisne           #+#    #+#             */
/*   Updated: 2023/04/10 16:23:12 by jlaisne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	get_pwd(t_minish *var)
{
	char	*str;

	str = get_cwd();
	if (str == NULL)
		exit_free(var);
	printf("%s\n", str);
	g_return_status = 0;
}

void	pwd_parsing(t_cmd *lst, t_minish *var)
{
	t_cmd	*opt;

	opt = get_node(lst, OPT, PIPE);
	if (opt)
		msg_invalid_opt(opt->content, "pwd", 2);
	else
		get_pwd(var);
}
