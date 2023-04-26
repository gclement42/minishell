/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cut_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gclement <gclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 09:33:31 by gclement          #+#    #+#             */
/*   Updated: 2023/04/26 12:25:55 by gclement         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	int	count_len_file(int *i, char *cmd)
{
	size_t	len;

	if (cmd[*i] == '"' || cmd[*i] == '\'')
	{
		len = count_len(&cmd[*i], cmd[*i]);
		*i += 1;
	}
	else
		len = count_len(&cmd[*i], ' ');
	if (count_len(&cmd[*i], '>') < len)
		len = count_len(&cmd[*i], '>');
	if (count_len(&cmd[*i], '<') < len)
		len = count_len(&cmd[*i], '<');
	return (len);
}

void	*get_file(char *cmd, int *i, t_cmd **lst)
{
	size_t	len;
	char	*word;

	while (cmd[*i])
	{
		if (cmd[*i] && (cmd[*i] == '"' || cmd[*i] == '\'' || cmd[*i] != ' '))
		{
			len = count_len_file(i, cmd);
			word = ft_substr(cmd, *i, len);
			if (!word)
				return (NULL);
			word = remove_quote(word);
			if (!word)
				return (NULL);
			*i += len;
			return (new_node_cmd(word, get_marks(cmd[*i - 1]), FILES, lst));
		}
		*i += 1;
	}
	return (NULL);
}

void	*get_redirect(char *cmd, int *i, t_cmd **lst, size_t *start)
{
	size_t	len;
	char	*word;
	int		tmp;

	tmp = *i;
	len = 1;
	while (cmd[*i] && (cmd[*i] == ' ' || cmd[*i] == '<' || cmd[*i] == '>'))
	{
		if (cmd[*i] == '<' || cmd[*i] == '>')
		{
			if (cmd[*i + 1] == cmd[*i])
				len = 2;
			word = ft_substr(cmd, *i, len);
			if (!word || !new_node_cmd(word, SPACES, REDIRECT, lst))
				return (NULL);
			*i += len;
			if (!get_file(cmd, i, lst))
				return (*start = *i + 1, NULL);
			*start = *i + 1;
			tmp = *i;
		}
		else
			*i += 1;
	}
	return (*i = tmp, lst);
}

void	*get_word(char *cmd, int *i, size_t *start, t_cmd **lst)
{
	size_t	len;
	char	*word;

	len = count_len(&cmd[*i], cmd[*i]);
	word = ft_substr(cmd, *i + 1, (len - 1));
	if (!word)
		return (NULL);
	check_is_opt_or_arg(word, cmd[*i], lst);
	if (!cmd[*i + len])
		*i += len;
	else if (cmd[*i + len + 1] != '\''
		&& cmd[*i + len + 1] != '"')
		*i += len + 1;
	else
		*i += len;
	*start = *i;
	return (lst);
}

void	get_frst_word(char *cmd, int *i, t_cmd **lst)
{
	size_t	len;
	char	*word;
	char	del;

	while (cmd[*i] && cmd[*i] == ' ')
		*i += 1;
	if (!cmd[*i])
		return ;
	len = *i;
	while (cmd[len] && cmd[len] != ' ' && cmd[len] != '>')
	{
		if (cmd[len] == '"' || cmd[len] == '\'')
		{
			del = cmd[len++];
			while (cmd[len] && cmd[len] != del)
				len++;
		}
		len++;
	}
	word = ft_substr(cmd, *i, len - *i);
	if (word && is_all_char(word, ' ') == 0)
		new_node_cmd(word, get_marks(cmd[*i]), CMD, lst);
	else
		return ;
	*i += (len - *i);
}
