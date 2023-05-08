/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gclement <gclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 12:25:34 by gclement          #+#    #+#             */
/*   Updated: 2023/05/08 13:24:36 by gclement         ###   ########.fr       */
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

int	skip_quote(int i, char *str, char del)
{
	int	len;

	len = 1;
	i++;
	while (str[i] && str[i] != del)
	{
		len++;
		i++;
	}
	if (str[i] == del)
		len++;
	return (len);
}

int	first_check_cmd(char *cmd)
{
	int	i;
	int	b;

	i = 0;
	b = 0;
	if (is_all_char(cmd, '|') || cmd[0] == '|')
		return (g_return_status = 2, free(cmd), \
			ft_putstr_fd(
				"minishell: syntax error near unexpected token `|'\n", 2), 0);
	while (cmd[i])
	{
		if (cmd[i] == '|')
		{
			if (b == 1)
				return (g_return_status = 2, free(cmd), \
				ft_putstr_fd(\
				"minishell: syntax error near unexpected token `|'\n", 2), 0);
			b = 1;
		}
		else if (cmd[i] != ' ')
			b = 0;
		i++;
	}
	return (1);
}

void	delete_tab(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\t')
			str[i] = ' ';
		i++;
	}
}
