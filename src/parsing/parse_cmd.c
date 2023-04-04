/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gclement <gclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 17:32:55 by gclement          #+#    #+#             */
/*   Updated: 2023/04/04 09:44:53 by gclement         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	char	**count_and_malloc(t_cmd *lst, int *len)
{
	t_cmd	*tmp;
	char	**arr_exec;

	tmp = lst;
	tmp = tmp->next;
	while (tmp)
	{
		if (tmp->type == S_SPACES)
			tmp = tmp->next;
		else
		{
			if (tmp->type != ARG && tmp->type != OPT)
				break ;
			*len += 1;
			tmp = tmp->next;
		}
	}
	arr_exec = malloc((*len + 1) * sizeof(char *));
	if (!arr_exec)
		return (NULL);
	return (arr_exec);
}

char	**create_arr_exec(t_cmd *cmd)
{
	char	**arr_exec;
	int		len;
	int		x;

	len = 1;
	x = 0;
	arr_exec = count_and_malloc(cmd, &len);
	while (x < len)
	{
		if (cmd->type != S_SPACES && \
		(cmd->type == OPT || cmd->type == ARG || cmd->type == CMD))
		{
			arr_exec[x] = cmd->content;
			x++;
		}
		cmd = cmd->next;
	}
	return (arr_exec[x] = NULL, arr_exec);
}

int	check_if_unexpected_token(t_cmd *node)
{
	int	i;

	i = 0;
	while (node && node->type != CMD)
		node = node->next;
	while (ft_isalnum(node->content[i]) || \
		(node->content[i] >= 33 && node->content[i] <= 47) ||
		node->content[i] == ' ')
		i++;
	if (node->content[i] || node->type == PIPE)
		return (msg_unexpected_token(node->content[i]), 0);
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
			if (word[ft_strlen(word) - 1] == ' ' && !split_word[x + 1] && !is_eol)
			{
				tmp = ft_strjoin(split_word[x], " ");
				check_is_opt_or_arg(tmp, ' ', lst);
				return (free(split_word[x]), free(split_word),free(word));
			}
			check_is_opt_or_arg(split_word[x], ' ', lst);
			x++;
			if (split_word[x])
				new_node_cmd(" ", -1, S_SPACES, lst);
		}
		return (free(word), free(split_word));
	}
	if (is_all_char(word, ' ') == 1)
	{
		new_node_cmd(" ", -1, S_SPACES, lst);
		free(word);
	}
	else
		check_is_opt_or_arg(word, SPACES, lst);
}
