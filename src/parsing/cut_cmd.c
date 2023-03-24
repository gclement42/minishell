/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cut_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gclement <gclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 09:33:31 by gclement          #+#    #+#             */
/*   Updated: 2023/03/24 16:56:33 by gclement         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_router(char *cmd, int *i, size_t *start, t_cmd **lst)
{
	char	*word;

	if (*start < ((size_t)*i) && cmd[*start] != '"' && cmd[*start] != '\'')
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
			if (!word)
				return (NULL);
			if (new_node_cmd(word, get_marks(cmd[*i]), FILES, lst) == NULL)
				return (NULL);
			*i += len - 1;
			return (word);
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
	while ((cmd[*i] == ' ' || cmd[*i] == '<' || cmd[*i] == '>') && cmd[*i])
	{
		if (cmd[*i] == '<' || cmd[*i] == '>')
		{
			if (cmd[*i + 1] == cmd[*i])
				len = 2;
			word = ft_substr(cmd, *i, len);
			if (!word)
				return ;
			if (new_node_cmd(word, SPACES, REDIRECT, lst) == NULL)
				return ;
			*i += len;
			if (get_file(cmd, i, lst) == NULL)
				return (ft_putstr_fd("minishell: syntax error near unexpected token `newline'\n", 2));
			*start = *i + 1;
			tmp = *i;
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
	if (!str)
		return (NULL);
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
		last->content = ft_strjoin(last->content, word);
	else if (word[tmp] == '-' && !ft_isalpha(word[x + 1]) && !get_node(*lst, ARG, PIPE))
		new_node_cmd(word, get_marks(marks), OPT, lst);
	else
	{
		if (is_all_char(word, ' ') == 0 || get_marks(marks) != SPACE)
			if (!new_node_cmd(word, get_marks(marks), ARG, lst))
				return ;
	}
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
	char	del;
	
	while (cmd[*i] == ' ')
		*i += 1;
	len = *i;
	while (cmd[len] && cmd[len] != ' ')
	{
		if (cmd[len] == '"' || cmd[len] == '\'')
		{
			del = cmd[len++];
			while (cmd[len] != del)
				len++;
		}
		len++;
	}
	word = ft_substr(cmd, *i, len - *i);
	word = remove_quote(word);
	if (is_all_char(word, ' ') == 0 && word)
		new_node_cmd(word, get_marks(cmd[*i]), CMD, lst);
	else
		return ;
	*i += len;
}

