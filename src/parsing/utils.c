/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaisne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 12:25:34 by gclement          #+#    #+#             */
/*   Updated: 2023/05/03 14:10:55 by jlaisne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_is_opt_or_arg(char *word, char marks, t_cmd **lst)
{
	int		x;
	int		beg;
	t_cmd	*last;

	x = 0;
	last = cmd_lst_last(lst);
	while (word[x] && (word[x] == '\'' || word[x] == '"'))
		x++;
	beg = x;
	while (word[x] && word[x] != ' ')
		x++;
	if (last && last->type == OPT && !ft_strchr(last->content, ' '))
	{
		last->content = ft_strjoin(last->content, word);
		if (!last->content)
			return ;
		if (ft_strchr(last->content, ' '))
			last->type = ARG;
	}
	else if (word[beg] && word[beg] == '-' && !get_node(*lst, ARG, PIPE))
		new_node_cmd(word, get_marks(marks), OPT, lst);
	else
		if (is_all_char(word, ' ') == 0 || get_marks(marks) != SPACE)
			if (!new_node_cmd(word, get_marks(marks), ARG, lst))
				return ;
}

void	skip_quote(int *i, char *str, char del)
{	
	*i += 1;
	while (str[*i] && str[*i] != del)
		*i += 1;
}
