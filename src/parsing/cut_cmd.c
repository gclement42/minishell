/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cut_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gclement <gclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 09:33:31 by gclement          #+#    #+#             */
/*   Updated: 2023/03/16 14:13:02 by gclement         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_file(char *cmd, int *i, t_cmd **lst)
{
	size_t	len;
	char	*word;

	if (cmd[*i] == '"' || cmd[*i] == '\'' || cmd[*i] != ' ')
	{
		if (cmd[*i] == '"' || cmd[*i] == '\'')
			len = count_len(&cmd[*i], cmd[*i]);
		else
			len = count_len(&cmd[*i], ' ');
		word = ft_substr(cmd, *i, len);
		if (!word)
			return ;
		if (new_node_cmd(word, get_marks(cmd[*i]), FILES, lst) == NULL)
			return ;
		*i += len;
		return ;
	}
}

void	get_redirect(char *cmd, int *i, t_cmd **lst, size_t *start)
{
	size_t	len;
	char	*word;
	int		tmp;

	tmp = *i;
	while ((cmd[*i] == ' ' || cmd[*i] == '<' || cmd[*i] == '>') && cmd[*i])
	{
		if (cmd[*i] == '<' || cmd[*i] == '>')
		{
			len = count_len(&cmd[*i], ' ');
			word = ft_substr(cmd, *i, len);
			if (!word)
				return ;
			if (new_node_cmd(word, SPACES, REDIRECT, lst) == NULL)
				return ;
			*i += len + 1;
			get_file(cmd, i, lst);
			*start = *i + 1;
			return ;
		}
		*i += 1;
	}
	*i = tmp;
}

static	char *remove_quote(char *str)
{
	int		i;
	char	*dest;
	int		x;
	char	tmp;

	i = -1;
	while (str[++i])
		if (!(str[i] == '\'' || str[i] == '"'))
			i += count_len(&str[i], str[i]);
	dest = ft_calloc((i + 1), sizeof(char));
	i = -1;
	x = -1;
	tmp = 0;
	while (str[++i] && dest)
	{
		if ((str[i] == '\'' || str[i] == '"') && tmp == 0)
			tmp = str[i++];
		if (str[i] == tmp)
		{
			tmp = 0;
			i++;
		}
		if ((str[i] == '\'' || str[i] == '"') && tmp == 0)
			tmp = str[i++];
		dest[++x] = str[i];
	}
	return (free(str), dest);
}

void	*get_word(char *cmd, int *i, size_t *start, t_cmd **lst)
{
	size_t	len;
	char	*word;

	if (*start < ((size_t)*i) && cmd[*start] != '"' && cmd[*start] != '\'')
	{
		word = ft_substr(cmd, *start, *i - *start);
		if (!word)
			return (NULL);
		get_word_with_space(word, lst, 0);
	}
	len = count_len(&cmd[*i], cmd[*i]);
	if (!cmd[*i + len])
		*i -= 1;
	word = ft_substr(cmd, *i + 1, (count_len(&cmd[*i], cmd[*i]) - 1));
	if (!word)
		return (NULL);
	if (new_node_cmd(word, get_marks(cmd[*i]), ARG, lst) == NULL)
		return (NULL);
	if (cmd[*i + len + 1] != '\'' && cmd[*i + len + 1] != '"')
		*i += len + 1;
	else
		*i += len;
	*start = *i;
	return (lst);
}

/* Surement des leaks ici */
void	get_frst_word(char *cmd, int *i, t_cmd **lst)
{
	size_t	len;
	char	*word;
	
	len = 0;
	while (cmd[*i] == ' ')
		*i += 1;
	while (len <= 1)
	{
		if (cmd[*i] == '\'' || cmd[*i] == '"')
			len = count_len(&cmd[*i], cmd[*i]);
		else
			len = count_len(&cmd[*i], ' ');
		if (len <= 1)
			*i += len + 1;
	}
	word = ft_substr(cmd, *i, len);
	if (is_all_spaces(word) == 0 && word)
	{
		word = remove_quote(word);
		new_node_cmd(word, get_marks(cmd[*i]), CMD, lst);
	}
	else
		return ;
	*i += len + 1;
}

void	get_opt(char *cmd, int *i, t_cmd **lst)
{
	char	*word;
	int		len;
	int		tmp;

	tmp = *i;
	while (cmd[*i])
	{
		while (cmd[*i] != '-' && \
			(cmd[*i] == ' ' || cmd[*i] == '\'' || cmd[*i] == '"' ) && cmd[*i])
			*i += 1;
		if (cmd[*i] == '-')
		{
			len = count_len(&cmd[*i], cmd[*i - 1]);
			word = ft_substr(cmd, *i, len);
			if (!word)
				return ;
			new_node_cmd(word, get_marks(cmd[tmp]), OPT, lst);
			*i += len;
			tmp = *i;
		}
		*i += 1;
	}
	*i = tmp;
}
