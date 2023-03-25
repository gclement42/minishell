/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gclement <gclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 17:32:55 by gclement          #+#    #+#             */
/*   Updated: 2023/03/24 17:00:58 by gclement         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_if_unexpected_token(t_cmd *node)
{
	int	i;

	i = 0;
	while (node && node->type != CMD)
		node = node->next; 
	while (ft_isalnum(node->content[i]) || \
		(node->content[i] >= 33 && node->content[i] <= 47) || node->content[i] == ' ')
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
		if (word[0] == ' ')
			new_node_cmd(" ", -1, S_SPACES, lst);
		while (split_word[x])
		{
			if (word[ft_strlen(word) - 1] == ' ' && !split_word[x + 1] && is_eol == 0)
			{
				tmp = ft_strjoin(split_word[x], " ");
				check_is_opt_or_arg(tmp, ' ', lst);
				return ;
			}
			check_is_opt_or_arg(split_word[x], ' ', lst);
			x++;
			if (split_word[x])
				new_node_cmd(" ", -1, S_SPACES, lst);
		}
		return ;
	}
	if (is_all_char(word, ' ') == 1)
		new_node_cmd(" ", -1, S_SPACES, lst);
	else
		check_is_opt_or_arg(word, SPACES, lst);
}
