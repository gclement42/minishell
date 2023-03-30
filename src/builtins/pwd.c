/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gclement <gclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 17:19:40 by jlaisne           #+#    #+#             */
/*   Updated: 2023/03/28 11:25:52 by gclement         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	get_pwd(void)
{
	char	*str;

	str = get_cwd();
	if (str == NULL)
		exit (1); // FREE
	printf("%s\n", str);
	return_status = 0;
}

void	pwd_parsing(t_cmd *lst)
{
	t_cmd	*opt;

	opt = get_node(lst, OPT, PIPE);
	if (opt)
		msg_invalid_opt(opt->content, "pwd");
	else
		get_pwd();
}
