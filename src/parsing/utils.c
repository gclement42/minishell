/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gclement <gclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 12:25:34 by gclement          #+#    #+#             */
/*   Updated: 2023/05/02 15:16:08 by gclement         ###   ########.fr       */
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

static char	*malloc_dest(char *cmd)
{
	int		count;
	int		i;
	char	*dest;

	i = 0;
	count = ft_strlen(cmd);
	while (cmd[i])
	{
		if (cmd[i] == '$'
			&& (cmd[i + 1] == '\'' || cmd[i + 1] == '"'))
			count--;
		i++;
	}
	dest = ft_calloc((count + 1), sizeof(char));
	if (!dest)
		return (NULL);
	else
		return (dest);
}

char	*delete_dollars(char *cmd)
{
	int		i;
	int		x;
	char	*dest;

	i = 0;
	x = 0;
	dest = malloc_dest(cmd);
	while (cmd[i])
	{
		if (!(cmd[i] == '$' && cmd[i + 1]
				&& (cmd[i + 1] == '\'' || cmd[i + 1] == '"')))
		{
			dest[x] = cmd[i];
			x++;
		}
		i++;
	}
	free(cmd);
	return (dest);
}
