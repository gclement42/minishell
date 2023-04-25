/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gclement <gclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 15:05:17 by gclement          #+#    #+#             */
/*   Updated: 2023/04/25 13:06:12 by gclement         ###   ########.fr       */
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
	while (cmd[i])
	{
		parse_router(cmd, &i, &start, lst);
		if (!cmd[i])
			break ;
		i++;
	}
	if (start < (size_t)i && cmd[start] && !is_all_char(&cmd[start], ' '))
	{
		word = ft_substr(cmd, start, ft_strlen(cmd) - start);
		if (!word)
			return (NULL);
		get_word_with_space(word, lst, 1);
	}
	return (*lst);
}

t_cmd	*create_lst_cmd(char *cmd, t_cmd *lst)
{
	char	**split_by_pipe;
	int		i;

	i = 0;
	if (is_all_char(cmd, '|') || cmd[0] == '|')
		return (g_return_status = 2, free(cmd), \
			ft_putstr_fd(
				"minishell: syntax error near unexpected token `|'\n", 2), NULL);
	split_by_pipe = ft_ms_split(cmd, '|');
	if (!split_by_pipe)
		return (free(cmd), NULL);
	while (split_by_pipe[i])
	{
		lst = parse_cmd(split_by_pipe[i], &lst);
		if (lst == NULL)
			return (free_2d_array(split_by_pipe), NULL);
		i++;
		if (split_by_pipe[i])
			new_node_cmd("|", SPACES, PIPE, &lst);
	}
	return (free_2d_array(split_by_pipe), lst);
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
		if (init_sigaction(new_signal_here_doc) == -1)
			exit_free(env);
	env->stdout_copy = dup(1);
	if (id == 0)
	{
		if (!get_node(lst, CMD, PIPE))
			search_if_redirect(env->pipex, lst, env);
		pipex(env, lst);
		free_cmd_list(lst);
		exit_free(env);
	}
}

static void	copystd_and_exec_builtins(t_cmd *arg, t_cmd *lst, t_minish *env)
{
	int		stdin_copy;
	int		stdout_copy;
	int		stderr_copy;

	(void) arg;
	if (!lst && check_if_unexpected_token(lst, env) == 0)
		return ;
	if (lst && count_type_in_lst(arg, PIPE, -1) == 0
		&& check_is_builtins(get_node(lst, CMD, PIPE), env) == 1)
	{
		stdin_copy = dup(0);
		stdout_copy = dup(1);
		stderr_copy = dup(2);
		close(0);
		close(1);
		close(2);
		builtins_router(
			get_node(lst, CMD, PIPE), count_type_in_lst(lst, ARG, PIPE), env);
		dup2(stdin_copy, 0);
		dup2(stdout_copy, 1);
		dup2(stderr_copy, 2);
	}
	errno = 0;
}

int	parsing(char *cmd, t_minish *env)
{
	t_cmd	*lst;
	t_cmd	*cmd_node;

	lst = NULL;
	if (!cmd || cmd[0] == '\0')
		return (g_return_status = 0);
	cmd = check_if_replace_var(cmd, env, 1);
	lst = create_lst_cmd(cmd, lst);
	if (!lst)
		return (-1);
	prompt_for_pipe(lst, cmd);
	if (cmd)
		free (cmd);
	env->cmd_lst = lst;
	cmd_node = get_node(lst, CMD, PIPE);
	if (cmd_node)
		cmd_node->content = remove_quote(cmd_node->content);
	fork_parsing(lst, env);
	wait(&env->status_parent);
	if (WEXITSTATUS(env->status_parent) || !WEXITSTATUS(env->status_parent))
		g_return_status = WEXITSTATUS(env->status_parent);
	copystd_and_exec_builtins(get_node(lst, ARG, PIPE), lst, env);
	return (free_cmd_list(lst), 1);
}
