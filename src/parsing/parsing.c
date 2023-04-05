/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaisne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 15:05:17 by gclement          #+#    #+#             */
/*   Updated: 2023/04/05 11:29:19 by jlaisne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_cmd	*parse_cmd(char *cmd, t_cmd **lst)
{
	int		i;
	size_t	start;
	char	*word;

	i = 0;
	get_redirect(cmd, &i, lst, &start);
	get_frst_word(cmd, &i, lst);
	start = i;
	while (cmd[i++])
	{
		if (cmd[i] == '\'' || cmd[i] == '"' \
			|| cmd[i] == '>' || cmd[i] == '<')
			parse_router(cmd, &i, &start, lst);
	}
	if (start < (size_t)i && cmd[start])
	{
		word = ft_substr(cmd, start, ft_strlen(cmd) - start);
		if (!word)
			return (NULL);
		if (is_all_char(word, ' ') == 0)
			get_word_with_space(word, lst, 1);
		else
			free (word);
	}
	return (*lst);
}

static	t_cmd	*create_lst_cmd(char *cmd, t_minish *env, int *b)
{
	char	**split_by_pipe;
	t_cmd	*lst;
	int		i;

	i = 0;
	*b = 0;
	lst = NULL;
	cmd = replace_variable(cmd, env, 1, b);
	if (is_all_char(cmd, '|') || cmd[0] == '|')
		return (ft_putstr_fd("bash: syntax error near unexpected token `|'\n", 2), NULL);
	split_by_pipe = ft_ms_split(cmd, '|');
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
	if (cmd[ft_strlen(cmd) - 1] == '|')
		new_node_cmd("|", SPACES, CMD, &lst);
	if (*b == 1)
		free (cmd);
	return (free_2d_array(split_by_pipe), lst);
}

int	is_here_doc(t_cmd *lst)
{
	if (ft_memcmp("<<", lst->content, ft_strlen(lst->content)) == 0)
		return (0);
	return (1);
}

static void	fork_parsing(t_cmd *lst, t_minish *env)
{
	pid_t	id;

	id = fork();
	if (id < 0)
		exit_free(env);
	if (init_sigaction(signal_parsing) == -1)
		exit_free(env);
	if (is_here_doc(lst) == 0)
	{
		if (init_sigaction(new_signal_here_doc) == -1)
			exit_free(env);
		if (termios_disable_quit() == 1)
			exit_free(env);
	}
	if (id == 0)
	{
		search_if_redirect(env->var, lst, env);
		pipex(env, lst);
		free_cmd_list(lst);
		if (env->var->env_cmd)
			free_2d_array(env->var->env_cmd);
		exit_free(env);
	}
}

static void	copystd_and_exec_builtins(t_cmd *lst, t_minish *env)
{
	t_cmd	*arg;
	int		stdin_copy;
	int		stdout_copy;
	int		stderr_copy;

	arg = get_node(lst, CMD, PIPE);
	if (!arg)
		return ;
	if (count_type_in_lst(lst, PIPE) == 0 && arg)
	{
		stdin_copy = dup(0);
		stdout_copy = dup(1);
		stderr_copy = dup(2);
		close(0);
		close(1);
		close(2);
		builtins_router(lst, count_type_in_lst(lst, ARG), env);
		dup2(stdin_copy, 0);
		dup2(stdout_copy, 1);
		dup2(stderr_copy, 2);
	}
}

int	parsing(char *cmd, t_minish *env)
{
	t_cmd	*lst;
	t_cmd	*cmd_node;
	int		b;

	if (!cmd || cmd[0] == '\0')
		return (g_return_status = 0);
	lst = create_lst_cmd(cmd, env, &b);
	if (!lst)
		return (-1);
	cmd_node = get_node(lst, CMD, PIPE);
	if (cmd_node)
		cmd_node->content = remove_quote(cmd_node->content);
	env->var = malloc(sizeof(t_pipex));
	if (!env->var)
		exit_env(env);
	fork_parsing(lst, env);
	wait(&env->var->status);
	if (WEXITSTATUS(env->var->status))
		g_return_status = WEXITSTATUS(env->var->status);
	copystd_and_exec_builtins(lst, env);
	return (1);
}
