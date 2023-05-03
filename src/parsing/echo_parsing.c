/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gclement <gclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 11:05:53 by gclement          #+#    #+#             */
/*   Updated: 2023/05/03 10:18:06 by gclement         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*join_all_arg(t_cmd *lst, int bools)
{
	char	*arg_join;
	char	*tmp;

	lst = get_node(lst, ARG, PIPE);
	tmp = ft_strdup(lst->content);
	lst = lst->next;
	arg_join = tmp;
	while (lst && (lst->type == ARG || lst->type == S_SPACES))
	{
		if (bools == 1 && lst->type == S_SPACES)
			break ;
		else
		{
			arg_join = ft_strjoin(tmp, lst->content);
			free (tmp);
			if (!arg_join)
				return (NULL);
			tmp = arg_join;
			lst = lst->next;
		}
	}
	return (arg_join);
}

void	check_opt(t_cmd *opt)
{
	int		i;

	while (opt && (opt->type == OPT || opt->type == S_SPACES))
	{
		if (opt->type == S_SPACES)
			opt = opt->next;
		else
		{
			i = 1;
			while (opt->content[i] == 'n')
				i++;
			if (opt->content[i])
				opt->type = ARG;
			opt = opt->next;
		}
	}
}

void	echo_parsing(t_cmd *lst, t_minish *var)
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
		arg_join = join_all_arg(lst, 0);
		if (!arg_join)
			exit_free(var);
	}
	if (get_node(lst, OPT, PIPE))
		print_echo(1, arg_join);
	else
		print_echo(0, arg_join);
	free (arg_join);
}
