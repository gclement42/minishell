/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaisne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 17:32:55 by gclement          #+#    #+#             */
/*   Updated: 2023/03/17 14:55:50 by jlaisne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_if_unexpected_token(t_cmd *node)
{
	int	i;

	i = 0;
	while (node && node->type != CMD)
		node = node->next; 
	while (ft_isalpha(node->content[i]) && node->content[i] != '$')
		i++;
	if (node->content[i] || node->type == PIPE)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
		ft_putchar_fd(node->content[i], 2);
		return (ft_putstr_fd("'\n", 2), 0);
	}
	return (1);
}

int	is_all_char(char *word, char c)
{
	int	x;

	x = 0;
	while (word[x])
	{
		if (word[x] != c)
			return (0);
		x++;
	}
	return (1);
}

void	get_word_with_space(char *word, t_cmd **lst, int is_eol)
{
	char	**split_word;
	int		x;
	char	*tmp;

	x = 0;
	if (ft_strchr(word, ' ') && is_all_char(word, ' ') == 0)
	{
		split_word = ft_split(word, ' ');
		while (split_word[x])
		{
			if (word[ft_strlen(word) - 1] == ' ' && !split_word[x + 1] && is_eol == 0)
			{
				tmp = ft_strjoin(split_word[x], " ");
				new_node_cmd(tmp, SPACES, ARG, lst);
				return ;
			}
			new_node_cmd(split_word[x], SPACES, ARG, lst);
			x++;
		}
		return ;
	}
	if (is_all_char(word, ' ') == 0)
		new_node_cmd(word, SPACES, ARG, lst);
}
