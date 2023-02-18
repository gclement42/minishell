/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gclement <gclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 15:05:17 by gclement          #+#    #+#             */
/*   Updated: 2023/02/18 14:24:18 by gclement         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


static void	get_redirect(char *cmd, int *i, t_cmd **lst)
{
	size_t	len;
	char	*word;
	int		tmp;

	tmp = *i;
	while ((cmd[*i] == ' ' || cmd[*i] == '<') && cmd[*i])
	{
		if (cmd[*i] == '<')
			new_node_cmd("<", SPACES, REDIRECT, lst);
		*i += 1;
		if (cmd[*i] == '"' || cmd[*i] == '\'' || cmd[*i] != ' ')
		{
			if (cmd[*i] == '"' || cmd[*i] == '\'')
				len = count_len(&cmd[*i], cmd[*i]);
			else
				len = count_len(&cmd[*i], ' ');
			word = ft_substr(cmd, *i, len);
			new_node_cmd(word, get_marks(cmd[*i]), FILES, lst);
			*i += len;
			return ;
		}
	}
	*i = tmp;
}

static void	get_word(char *cmd, int *i, size_t *start, t_cmd **lst)
{
	size_t	len;
	char	*word;
	t_type	type;

	type = ARG;
	if (*start < ((size_t)*i))
	{
		word = ft_substr(cmd, *start, *i - *start);
		new_node_cmd(word, SPACES, type, lst);
	}
	len = count_len(&cmd[*i], cmd[*i]);
	if (cmd[*i + len] != cmd[*i])
		cmd = prompt_for_quote_termination(cmd, cmd[*i]);
	word = ft_substr(cmd, *i + 1, (count_len(&cmd[*i], cmd[*i]) - 1));
	new_node_cmd(word, get_marks(cmd[*i]), type, lst);
	*i += len + 1;
	*start = *i + 1;
}

static	void	get_frst_word(char *cmd, int *i, t_cmd **lst)
{
	size_t	len;
	char	*word;

	len = count_len(&cmd[*i], ' ');
	word = ft_substr(&cmd[*i], 0, len);
	new_node_cmd(word, get_marks(cmd[*i]), CMD, lst);
	*i += len;
}

static	void	get_opt(char *cmd, int *i, t_cmd **lst)
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
		new_node_cmd(word, get_marks(cmd[tmp]), OPT, lst);
		*i += len + 1;
	}
	else
		*i = tmp;
}

static t_cmd	*parsing_true(char *cmd, t_cmd **lst)
{
	int		i;
	size_t	start;
	char	*word;

	i = 0;
	get_redirect(cmd, &i, lst);
	get_frst_word(cmd, &i, lst);
	get_opt(cmd, &i, lst);
	start = i;
	while (cmd[i])
	{
		if (cmd[i] == '\'' || cmd[i] == '"')
			get_word(cmd, &i, &start, lst);
		i++;
	}
	if (start < (size_t)i)
	{
		word = ft_substr(cmd, start, ft_strlen(cmd) - start);
		new_node_cmd(word, SPACES, ARG, lst);
	}
	return (*lst);
}

char	**parsing(char *cmd, t_minish env)
{
	t_cmd	*lst;
	char	**split_cmd;
	int		i;
	//char	**arg_exec;

	(void) env;
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
	while (lst)
	{
		printf("content = %s\n", lst->content);
		printf("marks = %d\n", lst->marks);
		printf("type = %d\n\n", lst->type);
		lst = lst->next;
	}
	// arg_exec = set_argxec(split_cmd);
	// if (!arg_exec)
	// 	free_2d_array(arg_exec);
	// (void) env;
	// if (check_is_builtins(split_cmd[0], env) == 1)
	// 	builtins_parsing(arg_exec, count_nb_arg(arg_exec));
	return (NULL);
}
