/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gclement <gclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 15:05:17 by gclement          #+#    #+#             */
/*   Updated: 2023/02/25 17:33:40 by gclement         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// // static t_cmd	*replace_variable(t_cmd *lst, t_minish env)
// // {
// // 	return ;
// // }

static t_cmd	*parsing_true(char *cmd, t_cmd **lst)
{
	int		i;
	size_t	start;
	char	*word;

	i = 0;
	get_redirect(cmd, &i, lst, &start);
	get_frst_word(cmd, &i, lst);
	get_opt(cmd, &i, lst);
	start = i;
	while (cmd[i])
	{
		if (cmd[i] == '\'' || cmd[i] == '"')
			get_word(cmd, &i, &start, lst);
		if (cmd[i] == '>')
			get_redirect(cmd, &i, lst, &start);
		i++;
	}
	if (start < (size_t)i)
	{
		word = ft_substr(cmd, start, ft_strlen(cmd) - start);
		if (!word)
			return (NULL);
		new_node_cmd(word, SPACES, ARG, lst);
	}
	return (*lst);
}

char	**parsing(char *cmd, t_minish *env)
{
	t_cmd	*lst;
	t_cmd	*tmp;
	char	**split_cmd;
	int		i;
	int		count;

	i = 0;
	lst = NULL;
	split_cmd = ft_split(cmd, '|');
	while (split_cmd[i])
	{
		lst = parsing_true(split_cmd[i], &lst);
		i++;
		if (split_cmd[i])
			new_node_cmd("|", SPACES, PIPE, &lst);
	}
	tmp = lst;
	count = 0;
	while (tmp)
	{
		printf("content = %s\n", tmp->content);
		printf("marks = %d\n", tmp->marks);
		printf("type = %d\n\n", tmp->type);
		if (tmp->type == ARG)
			count++;
		tmp = tmp->next;
	}
	if (check_is_builtins(get_node(lst, CMD), env) == 1)
		builtins_parsing(lst, count, env);
	return (NULL);
}
