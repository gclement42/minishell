/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gclement <gclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 15:05:17 by gclement          #+#    #+#             */
/*   Updated: 2023/03/21 10:43:57 by jlaisne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**create_arr_exec(t_cmd *cmd)
{
	t_cmd	*tmp;
	char	**arr_exec;
	int		len;
	int		x;

	len = 1;
	x = -1;
	tmp = cmd;
	tmp = tmp->next;
	while (tmp)
	{
		if (tmp->type != ARG && tmp->type != OPT)
			break;
		len++;
		tmp = tmp->next;
	}
	arr_exec = malloc((len + 1) * sizeof(char *));
	if (!arr_exec)
		return (NULL);
	while (++x < len)
	{
		arr_exec[x] = cmd->content;
		cmd = cmd->next;
	}
	return (arr_exec[x] = NULL, arr_exec);
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
		get_word_with_space(word, lst, 1);
	}
	return (*lst);
}

static	t_cmd *create_lst_cmd(char *cmd, t_minish *env)
{
	char	**split_by_pipe;
	t_cmd	*lst;
	int		i;
	
	i = 0;
	lst = NULL;
	if (is_all_char(cmd, '|') || cmd[0] == '|')
		return (ft_putstr_fd("bash: syntax error near unexpected token `|'\n", 2), NULL);
	split_by_pipe = ft_split(cmd, '|');
	if (!split_by_pipe)
		return (NULL);
	while (split_by_pipe[i])
	{
		lst = parse_cmd(split_by_pipe[i], &lst);
		if (lst == NULL)
			return (free_2d_array(split_by_pipe), NULL);
		i++;
		if (split_by_pipe[i])
			new_node_cmd("|", SPACES, PIPE, &lst);
	}
	replace_variable(lst, env);
	return (free_2d_array(split_by_pipe), lst);
}

int is_here_doc(t_cmd *lst)
{
	if (ft_memcmp("<<", lst->content, ft_strlen(lst->content)) == 0)
		return (0);
	return (1);
}

int	parsing(char *cmd, t_minish *env)
{
	t_cmd	*lst;
	pid_t	id;

	if (!cmd || cmd[0] == '\0')
	{
		return_status = 0;
		return (1);
	}
	lst = create_lst_cmd(cmd, env);
	if (!lst)
		return (-1); //FREE
	env->var = malloc(sizeof(t_pipex));
	if (!env->var)
		exit (1); //FREE
	id = fork();
	if (id < 0)
		exit (1); // FREE
	init_sigaction(signal_parsing);
	if (is_here_doc(lst) == 0)
	{
		init_sigaction(new_signal_here_doc);
		if (termios_disable_quit() == 1)
			exit (1); // FREE
	}
	if (id == 0)
	{
		search_if_redirect(env->var, lst);
		if (!(count_type_in_lst(lst, PIPE) == 0 
			&& check_is_builtins(get_node(lst, CMD), env)))
			pipex(env, lst);
		free_cmd_list(lst);
		exit(return_status);
	}
	wait(&env->var->status);
	if (WEXITSTATUS(env->var->status))
		return_status = WEXITSTATUS(env->var->status);
	if (count_type_in_lst(lst, PIPE) == 0 
		&& check_is_builtins(get_node(lst, CMD), env))
		builtins_router(lst, count_type_in_lst(lst, ARG), env);
	return (free_cmd_list(lst), 1);
}
