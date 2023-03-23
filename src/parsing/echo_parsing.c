/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gclement <gclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 11:05:53 by gclement          #+#    #+#             */
/*   Updated: 2023/03/23 11:48:33 by gclement         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*join_all_arg(t_cmd *lst)
{
	char	*arg_join;
	char	*tmp;
	//char	*add_space;

	lst = get_node(lst, ARG, PIPE);
	tmp = lst->content;
	lst = lst->next;
	arg_join = tmp;
	while (lst && (lst->type == ARG || lst->type == S_SPACES))
	{
		// if (lst->marks == SPACES)
		// {
		// 	add_space = ft_strjoin(tmp, " ");
		// 	arg_join = ft_strjoin(add_space, lst->content);
		// 	free (add_space);
		// }
		arg_join = ft_strjoin(tmp, lst->content);
		if (!arg_join)
			return (NULL);
		free (tmp);
		tmp = arg_join;
		lst = lst->next;
	}
	return (arg_join);
}

void	check_opt(t_cmd *opt)
{
	int		i;
	
	while (opt && opt->type == OPT)
	{
		i = 1;
		while (opt->content[i] == 'n')
			i++;
		if (opt->content[i] && opt->content[i] != ' ')
			opt->type = ARG;
		opt = opt->next;
	}
}

void	echo_parsing(t_cmd *lst)
{
	char	*arg_join;
	t_cmd	*opt;

	arg_join = NULL;
	if (lst->next)
		lst = lst->next;
	else
		return (print_echo(0, NULL));
	opt = get_node(lst, OPT, PIPE);
	if (opt)
		check_opt(opt);
	if (get_node(lst, ARG, PIPE))
	{
		arg_join = join_all_arg(lst);
		if (!arg_join)
			exit (0);
	}
	if (get_node(lst, OPT, PIPE))
	{
		printf("la\n");
		print_echo(1, arg_join);
	}
	else
	{
		printf("ici\n");
		print_echo(0, arg_join);
	}
}
