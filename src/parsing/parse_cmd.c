/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gclement <gclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 17:32:55 by gclement          #+#    #+#             */
/*   Updated: 2023/03/02 13:50:16 by gclement         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_all_spaces(char *word)
{
	int	x;

	x = 0;
	while (word[x])
	{
		if (word[x] != ' ')
			return (0);
		x++;
	}
	return (1);
}

void	get_word_with_space(char *word, t_cmd **lst)
{
	char	**split_word;
	int		x;
	char	*tmp;

	x = 0;
	if (ft_strchr(word, ' ') && is_all_spaces(word) == 0)
	{
		split_word = ft_split(word, ' ');
		while (split_word[x])
		{
			if (word[ft_strlen(word) - 1] == ' ' && !split_word[x + 1])
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
	new_node_cmd(word, SPACES, ARG, lst);
}
