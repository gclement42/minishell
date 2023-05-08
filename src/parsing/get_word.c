/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_word.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gclement <gclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 09:33:31 by gclement          #+#    #+#             */
/*   Updated: 2023/05/08 10:10:04 by gclement         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static	int	count_len_frst_word(char *cmd, int len)
{
	char	del;

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
	return (len);
}

int	get_frst_word(char *cmd, int *i, t_cmd **lst, t_minish *env)
{
	size_t	len;
	char	*word;

	cmd = check_if_replace_var_in_str(cmd, ' ', env);
	while (cmd[*i] && cmd[*i] == ' ')
		*i += 1;
	if (!cmd[*i])
		return (1);
	len = count_len_frst_word(cmd, *i);
	word = ft_substr(cmd, *i, len - *i);
	if (!word)
		return (0);
	word = remove_quote(word);
	if (!word)
		return (0);
	if (is_all_char(word, ' ') == 0)
		new_node_cmd(word, get_marks(cmd[*i]), CMD, lst);
	else
		return (free(word), free(cmd), \
		ft_putstr_fd("minishell : Command '' not found\n", 2), \
		g_return_status = 127, 0);
	*i += (len - *i);
	return (1);
}
