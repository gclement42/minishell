/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gclement <gclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 15:05:17 by gclement          #+#    #+#             */
/*   Updated: 2023/03/08 17:10:31 by gclement         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	builtins_router(t_cmd *lst, int argc, t_minish *var)
{
	t_cmd	*cmd_node;
	t_cmd	*arg_node;
	t_env	*env_lst;
	size_t	cmd_len;

	cmd_node = get_node(lst, CMD);
	arg_node = get_node(lst, ARG);
	cmd_len = ft_strlen(cmd_node->content);
	if (ft_memcmp(cmd_node->content, "env", cmd_len) == 0
		|| ft_memcmp(cmd_node->content, "export", cmd_len) == 0)
		env_lst = export_variable_parsing(lst, cmd_node->content);
	if (ft_memcmp(cmd_node->content, "cd", cmd_len) == 0)
		cd_parsing(arg_node, argc, var);
	if (ft_memcmp(cmd_node->content, "pwd", cmd_len) == 0)
		get_pwd(var);
	if (ft_memcmp(cmd_node->content, "env", cmd_len) == 0)
		get_env(var, &env_lst);
	if (ft_memcmp(cmd_node->content, "unset", cmd_len) == 0)
		unset_parsing(var, arg_node);
	if (ft_memcmp(cmd_node->content, "export", cmd_len) == 0)
		export_parsing(var, argc, env_lst, arg_node);
	if (ft_memcmp(cmd_node->content, "echo", cmd_len) == 0)
		echo_parsing(cmd_node);
	if (ft_memcmp(cmd_node->content, "exit", cmd_len) == 0)
		exit_parsing(var, arg_node);
}

char	**create_arr_exec(t_cmd *cmd)
{
	t_cmd	*tmp;
	char	**arr_exec;
	int		len;
	int		x;

	len = 0;
	x = 0;
	tmp = cmd;
	while (tmp)
	{
		if (tmp->type == PIPE)
			break;
		len++;
		tmp = tmp->next;
	}
	arr_exec = malloc((len + 1) * sizeof(char *));
	if (!arr_exec)
		return (NULL);
	while (x < len)
	{
		arr_exec[x] = cmd->content;
		cmd = cmd->next;
		x++;
	}
	arr_exec[x] = NULL;
	return (arr_exec);
}

static t_cmd	*parse_cmd(char *cmd, t_cmd **lst)
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
		if (cmd[i] == '>' || cmd[i] == '<')
			get_redirect(cmd, &i, lst, &start);
		i++;
	}
	if (start < (size_t)i - 1 && cmd[start])
	{
		word = ft_substr(cmd, start, ft_strlen(cmd) - start);
		if (!word)
			return (NULL);
		get_word_with_space(word, lst);
	}
	return (*lst);
}

static	t_cmd *create_lst_cmd(char *cmd)
{
	char	**split_by_pipe;
	char	**tok_split;
	t_cmd	*lst;
	int		i;
	int		x;
	
	i = 0;
	x = -1;
	lst = NULL;
	split_by_pipe = ft_split(cmd, '|');
	if (!split_by_pipe)
		return (NULL)
	while (split_by_pipe[i])
	{
		tok_split = ft_strtok(split_by_pipe[i], ";&");
		if (!tok_split)
			return (NULL);
		while (tok_split[++x])
			lst = parse_cmd(tok_split[x], &lst);
		i++;
		if (split_by_pipe[i])
			new_node_cmd("|", SPACES, PIPE, &lst);
	}
	return (free_2d_array(split_by_pipe), free_2d_array(tok_split), lst);
}



void	parsing(char *cmd, t_minish *env)
{
	t_cmd	*lst;
	int 	pipe_fd[2];

	if (cmd[0] == '\0')
		return ;
	lst = create_lst_cmd(cmd);
	if (!lst)
		exit (0);
	replace_variable(lst, env);
	search_if_redirect(env->var, lst, pipe_fd);
	env->env_tab = lst_to_tab(&env->env_list);
	if (!env->env_tab)
		exit (1); //FREE
	if (count_type_in_lst(lst, PIPE) == 0 
		&& check_is_builtins(get_node(lst, CMD), env))
		builtins_router(lst, count_type_in_lst(lst, ARG), env);
	else
		pipex(env, lst);
	return ;
}