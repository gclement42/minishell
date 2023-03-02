/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaisne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 15:05:17 by gclement          #+#    #+#             */
/*   Updated: 2023/03/02 14:47:20 by jlaisne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static t_cmd	*replace_variable(t_cmd *lst, t_minish *env)
{
	char	*new_content;

	while (lst)
	{
		if (lst->content[0] == '$' && lst->marks != QUOTE)
		{
			new_content = search_key(env->env_list, &lst->content[1]);
			free(lst->content);
			if (new_content)
				lst->content = new_content;
			else
				lst->content = " ";
		}
		lst = lst->next;
	}
	return (lst);
}

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
		while (cmd[start] == ' ')
			start++;
		word = ft_substr(cmd, start, ft_strlen(cmd) - start);
		if (!word)
			return (NULL);
		get_word_with_space(word, lst);
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

	if (cmd[0] == '\0')
		return (NULL);
	i = 0;
	lst = NULL;
	split_cmd = ft_split(cmd, '|'); //protect
	while (split_cmd[i])
	{
		lst = parsing_true(split_cmd[i], &lst);
		i++;
		if (split_cmd[i])
			new_node_cmd("|", SPACES, PIPE, &lst);
	}
	tmp = lst;
	count = 0;
	replace_variable(lst, env);
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

void	builtins_parsing(t_cmd *lst, int argc, t_minish *var)
{
	t_cmd	*cmd_node;
	t_cmd	*arg_node;
	t_env	*env_lst;
	size_t	cmd_len;

	cmd_node = get_node(lst, CMD);
	arg_node = get_node(lst, ARG);
	cmd_len = ft_strlen(cmd_node->content);
	env_lst = export_variable_parsing(lst, cmd_node->content);
	if (ft_memcmp(cmd_node->content, "cd", cmd_len) == 0)
		cd_parsing(arg_node, argc, var);
	if (ft_memcmp(cmd_node->content, "pwd", cmd_len) == 0)
		get_pwd(var);
	if (ft_memcmp(cmd_node->content, "env", cmd_len) == 0)
		get_env(var, &env_lst);
	if (ft_memcmp(cmd_node->content, "unset", cmd_len) == 0)
		unset_parsing(var, arg_node);
	if (ft_memcmp(cmd_node->content, "export", 6) == 0)
		export_env(var, env_lst, argc);
	if (ft_memcmp(cmd_node->content, "echo", 4) == 0)
		echo_parsing(cmd_node);
	if (ft_memcmp(cmd_node->content, "exit", 4) == 0)
		exit_parsing(var, arg_node);
}
