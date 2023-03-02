/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cut_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaisne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 09:33:31 by gclement          #+#    #+#             */
/*   Updated: 2023/03/02 14:37:25 by jlaisne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

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

void	get_word(char *cmd, int *i, size_t *start, t_cmd **lst)
{
	size_t	len;
	char	*word;
	t_type	type;

	type = ARG;
	if (*start < ((size_t)*i))
	{
		word = ft_substr(cmd, *start, *i - *start);
		if (!word)
			return ;
		get_word_with_space(word, lst);
	}
	len = count_len(&cmd[*i], cmd[*i]);
	if (cmd[*i + len] != cmd[*i])
		cmd = prompt_for_quote_termination(cmd, cmd[*i]);
	word = ft_substr(cmd, *i + 1, (count_len(&cmd[*i], cmd[*i]) - 1));
	if (!word)
		return ;
	if (new_node_cmd(word, get_marks(cmd[*i]), type, lst) == NULL)
		return ;
	*i += len + 1;
	*start = *i;
}

void	get_frst_word(char *cmd, int *i, t_cmd **lst)
{
	size_t	len;
	char	*word;

	len = count_len(&cmd[*i], ' ');
	word = ft_substr(&cmd[*i], 0, len);
	if (!word)
		return ;
	new_node_cmd(word, get_marks(cmd[*i]), CMD, lst);
	*i += len;
}

void	get_opt(char *cmd, int *i, t_cmd **lst)
{
	char	*word;
	int		len;
	int		tmp;

	tmp = *i;
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
		*i += len + 1;
	}
	else
		*i = tmp;
}
