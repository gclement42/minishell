/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_redirect.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gclement <gclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 10:03:57 by gclement          #+#    #+#             */
/*   Updated: 2023/05/02 10:42:58 by gclement         ###   ########.fr       */
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
			if (word[0] == '<' || word[0] == '>')
				return (msg_unexpected_token(word[0]), NULL);
			word = remove_quote(word);
			if (!word)
				return (NULL);
			*i += len;
			if (word)
				return (new_node_cmd(word, get_marks(cmd[*i - 1]), FILES, lst));
			else
				return (msg_unexpected_token(0), NULL);
		}
		*i += 1;
	}
	return (msg_unexpected_token(0), NULL);
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
