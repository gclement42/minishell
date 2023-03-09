/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cut_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gclement <gclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 09:33:31 by gclement          #+#    #+#             */
/*   Updated: 2023/03/09 13:20:55 by gclement         ###   ########.fr       */
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

void	get_word(char *cmd, int *i, size_t *start, t_cmd **lst)
{
	size_t	len;
	char	*word;

	if (*start < ((size_t)*i) && cmd[*start] != '"' && cmd[*start] != '\'')
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
	if (new_node_cmd(word, get_marks(cmd[*i]), ARG, lst) == NULL)
		return ;
	if (cmd[*i + len + 1] != '\'' && cmd[*i + len + 1] != '"')
		*i += len + 1;
	else
		*i += len;
	*start = *i;
}

/* Surement des leaks ici */
void	get_frst_word(char *cmd, int *i, t_cmd **lst)
{
	size_t	len;
	char	*word;
	int		x;

	x = 0;
	len = count_len(&cmd[*i], ' ');
	word = ft_substr(cmd, 0, len);
	if (!word)
		return ;
	while (word[x] == ' ')
		x++;
	new_node_cmd(&word[x], get_marks(cmd[*i]), CMD, lst);
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
