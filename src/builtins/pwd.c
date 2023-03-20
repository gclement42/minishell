/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gclement <gclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 17:19:40 by jlaisne           #+#    #+#             */
/*   Updated: 2023/03/20 13:54:35 by gclement         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	get_pwd(t_minish *var)
{
	t_env *temp;
	char *str;

	temp = var->env_list;
	if (temp)
	{
		var->pwd = NULL;
		if (check_key(&(var->env_list), "PWD") == 0)
		{
			while (temp->next)
			{
				if (ft_strnstr(temp->key, "PWD", 4))
					break ;
				temp = temp->next;
			}
			var->pwd = ft_strdup(temp->content);
			printf("%s\n", var->pwd);
			free(var->pwd);
		}
		else
		{
			str = get_cwd();
			printf("%s\n", str);
		}
	}
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
