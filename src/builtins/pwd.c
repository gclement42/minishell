/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaisne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 17:19:40 by jlaisne           #+#    #+#             */
/*   Updated: 2023/05/03 10:45:15 by jlaisne          ###   ########.fr       */
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
	int		i;

	opt = get_node(lst, OPT, PIPE);
	while (opt && (opt->type == OPT || opt->type == S_SPACES))
	{
		i = 0;
		while (opt->content[i])
		{
			if (opt->content[i] != '-')
				return (msg_invalid_opt(opt->content, "pwd", 2));
			i++;
		}
		if (i > 2)
			return (msg_invalid_opt(opt->content, "pwd", 2));
		opt = opt->next;
	}
	get_pwd(var);
}
