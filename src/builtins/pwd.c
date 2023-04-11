/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gclement <gclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 17:19:40 by jlaisne           #+#    #+#             */
/*   Updated: 2023/04/11 09:19:25 by gclement         ###   ########.fr       */
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
	free(str);
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
