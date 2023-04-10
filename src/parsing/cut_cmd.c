/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cut_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaisne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 09:33:31 by gclement          #+#    #+#             */
/*   Updated: 2023/04/06 16:10:52 by gclement         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*get_file(char *cmd, int *i, t_cmd **lst)
{
	size_t	len;
	char	*word;

	while (cmd[*i])
	{
		if (cmd[*i] && (cmd[*i] == '"' || cmd[*i] == '\'' || cmd[*i] != ' '))
		{
			if (cmd[*i] == '"' || cmd[*i] == '\'')
			{
				len = count_len(&cmd[*i], cmd[*i]) - 1;
				*i += 1;
			}
			else
				len = count_len(&cmd[*i], ' ');
			if (count_len(&cmd[*i], '>') < len)
				len = count_len(&cmd[*i], '>');
			if (count_len(&cmd[*i], '<') < len)
				len = count_len(&cmd[*i], '<');
			word = ft_substr(cmd, *i, len);
			if (!word || !new_node_cmd(word, get_marks(cmd[*i]), FILES, lst))
				return (NULL);
			return (*i += len, word);
		}
		*i += 1;
	}
	return (NULL);
}

void	get_redirect(char *cmd, int *i, t_cmd **lst, size_t *start)
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
			if (!word || new_node_cmd(word, SPACES, REDIRECT, lst) == NULL)
				return ;
			*i += len;
			if (get_file(cmd, i, lst) == NULL)
				return ;
			*start = *i + 1;
			tmp = *i;
		}
		else
			*i += 1;
	}
	*i = tmp;
}

void	check_is_opt_or_arg(char *word, char marks, t_cmd **lst)
{
	int		x;
	int		tmp;
	t_cmd	*last;

	x = 0;
	last = cmd_lst_last(lst);
	while (word[x] && (word[x] == '\'' || word[x] == '"'))
		x++;
	tmp = x;
	while (word[x] && word[x] != ' ')
		x++;
	if (last->type == OPT && !ft_strchr(last->content, ' '))
	{
		last->content = ft_strjoin(last->content, word);
		if (ft_strchr(last->content, ' '))
			last->type = ARG;
	}
	else if (word[tmp] && word[tmp] == '-' && !ft_isalpha(word[x + 1])
		&& !get_node(*lst, ARG, PIPE))
		new_node_cmd(word, get_marks(marks), OPT, lst);
	else
		if (is_all_char(word, ' ') == 0 || get_marks(marks) != SPACE)
			if (!new_node_cmd(word, get_marks(marks), ARG, lst))
				return ;
}

void	*get_word(char *cmd, int *i, size_t *start, t_cmd **lst)
{
	size_t	len;
	char	*word;

	len = count_len(&cmd[*i], cmd[*i]);
	// if (!cmd[*i + len])
	// 	*i -= 1;
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

/* Surement des leaks ici */
void	get_frst_word(char *cmd, int *i, t_cmd **lst)
{
	size_t	len;
	char	*word;
	char	del;

	while (cmd[*i] == ' ')
		*i += 1;
	len = *i;
	while (cmd[len] && cmd[len] != ' ')
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

