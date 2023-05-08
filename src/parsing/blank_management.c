/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blank_management.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gclement <gclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 10:57:56 by gclement          #+#    #+#             */
/*   Updated: 2023/05/08 10:18:08 by gclement         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_router(char *cmd, int *i, size_t *start, t_cmd **lst)
{
	char	*word;
	size_t	tmp;

	tmp = *i;
	if (cmd[*i] == '\'' || cmd[*i] == '"' \
	|| cmd[*i] == '>' || cmd[*i] == '<')
	{
		if (*start < tmp && \
			cmd[*start] != '"' && cmd[*start] != '\'')
		{
			word = ft_substr(cmd, *start, *i - *start);
			if (!word)
				return ;
			get_word_with_space(word, lst, 0);
		}
		if (cmd[*i] == '\'' || cmd[*i] == '"')
			get_word(cmd, i, start, lst);
		if (cmd[*i] == '>' || cmd[*i] == '<')
			get_redirect(cmd, i, lst, start);
	}
}

static char	*malloc_dest(char *str)
{
	int		i;
	char	*dest;

	i = 0;
	if (!str)
		return (NULL);
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
			i += skip_quote(i, str, str[i]);
		else
			i++;
	}
	dest = ft_calloc((i + 1), sizeof(char));
	if (!dest)
		return (NULL);
	return (dest);
}

char	*remove_quote(char *str)
{
	int		i;
	char	*dest;
	int		x;
	char	tmp;

	i = 0;
	x = -1;
	tmp = 0;
	dest = malloc_dest(str);
	while (dest && str[i])
	{
		if ((str[i] == '\'' || str[i] == '"') && tmp == 0)
			tmp = str[i];
		else if (str[i] == tmp)
			tmp = 0;
		else if (str[i] != tmp)
			dest[++x] = str[i];
		i++;
		if (!str[i])
			break ;
	}
	return (free(str), dest);
}

static void	split_word_by_space(char *word, t_cmd **lst, int is_eol)
{
	int		x;
	char	**split_word;

	x = 0;
	split_word = ft_split(word, ' ');
	while (split_word[x])
	{
		check_is_opt_or_arg(split_word[x], ' ', lst);
		if (word[ft_strlen(word) - 1] == ' ' && !split_word[x + 1] && !is_eol)
			new_node_cmd(" ", -1, S_SPACES, lst);
		x++;
		if (split_word[x])
			new_node_cmd(" ", -1, S_SPACES, lst);
	}
	return (free(word), free(split_word));
}

void	get_word_with_space(char *word, t_cmd **lst, int is_eol)
{
	if (word[0] == ' ')
	{
		new_node_cmd(" ", -1, S_SPACES, lst);
		if (!(ft_strchr(word, ' ') && is_all_char(word, ' ') == 0))
			return (free (word));
	}
	if (ft_strchr(word, ' ') && is_all_char(word, ' ') == 0)
		return (split_word_by_space(word, lst, is_eol));
	if (is_all_char(word, ' ') == 1 && word[0] != ' ')
	{
		new_node_cmd(" ", -1, S_SPACES, lst);
		free(word);
	}
	else if (word[0] != ' ')
		check_is_opt_or_arg(word, SPACES, lst);
}
