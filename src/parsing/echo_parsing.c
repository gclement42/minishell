/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gclement <gclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 11:05:53 by gclement          #+#    #+#             */
/*   Updated: 2023/03/02 10:42:27 by gclement         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*join_all_arg(t_cmd *lst)
{
	char	*arg_join;
	char	*tmp;
	char	*add_space;

	lst = get_node(lst, ARG);
	tmp = lst->content;
	lst = lst->next;
	arg_join = tmp;
	while (lst && lst->type == ARG)
	{
		if (lst->marks == SPACES)
		{
			add_space = ft_strjoin(tmp, " ");
			arg_join = ft_strjoin(add_space, lst->content);
			free (add_space);
		}
		else
			arg_join = ft_strjoin(tmp, lst->content);
		if (!arg_join)
			return (NULL);
		free (tmp);
		tmp = arg_join;
		lst = lst->next;
	}
	return (arg_join);
}

void	echo_parsing(t_cmd *lst)
{
	int		i;
	char	*arg_join;
	int		opt;

	i = 1;
	lst = lst->next;
	opt = 0;
	if (lst->type == OPT)
	{
		opt = 1;
		while (lst->content[i] == 'n')
			i++;
		if (lst->content[i])
		{
			lst->type = ARG;
			opt = 0;
		}
	}
	arg_join = join_all_arg(lst);
	if (!arg_join)
		exit (0);
	if (opt == OPT)
		print_echo(1, arg_join);
	else
		print_echo(0, arg_join);
}
