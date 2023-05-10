/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaisne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 15:05:17 by gclement          #+#    #+#             */
/*   Updated: 2023/05/10 11:22:19 by jlaisne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_cmd	*parse_cmd(char *cmd, t_cmd **lst, t_minish *env)
{
	int		i;
	size_t	start;
	char	*word;

	i = 0;
	cmd = check_if_replace_var_in_str(cmd, ' ', env);
	get_redirect(cmd, &i, lst, &start);
	if (!get_frst_word(cmd, &i, lst, env))
		return (NULL);
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
	return (free(cmd), *lst);
}

t_cmd	*create_lst_cmd(char *cmd, t_cmd *lst, t_minish *env)
{
	char	**split_by_pipe;
	int		i;

	i = 0;
	if (cmd[0] == '\0' || is_all_char(cmd, ' '))
		return (g_return_status = 0, free(cmd), NULL);
	if (!first_check_cmd(cmd))
		return (NULL);
	split_by_pipe = ft_ms_split(cmd, '|');
	if (!split_by_pipe)
		return (free(cmd), NULL);
	while (split_by_pipe[i])
	{
		lst = parse_cmd(split_by_pipe[i], &lst, env);
		if (lst == NULL)
			return (free(split_by_pipe), free(cmd), NULL);
		i++;
		if (split_by_pipe[i])
			new_node_cmd("|", SPACES, PIPE, &lst);
	}
	return (free(split_by_pipe), lst);
}

static void	fork_parsing(t_cmd *lst, t_minish *env)
{
	pid_t	id;
	t_cmd	*temp;

	id = fork();
	if (id < 0)
		exit_free(env);
	if (init_sigaction(signal_parsing) == -1)
		exit_free(env);
	temp = lst;
	while (temp && is_here_doc(temp) != 0)
		temp = temp->next;
	if (temp && is_here_doc(temp) == 0)
		if (init_sigaction(new_signal_here_doc) == -1)
			exit_free(env);
	env->stdout_copy = dup(1);
	if (env->stdout_copy == -1)
		return (perror("dup"), free_cmd_list(lst), exit_free(env));
	if (id == 0)
	{
		if (!get_node(lst, CMD, PIPE))
			search_if_redirect(lst, env);
		pipex(env, lst);
		free_cmd_list(lst);
		exit_free(env);
	}
}

static void	copystd_and_exec_builtins(t_cmd *lst, t_minish *env)
{
	int		stdin_copy;
	int		stdout_copy;
	int		stderr_copy;

	if (!lst && check_if_unexpected_token(lst, env) == 0)
		return ;
	if (lst && count_type_in_lst(lst, PIPE, -1) == 0
		&& check_is_builtins(get_node(lst, CMD, PIPE), env) == 1)
	{
		stdin_copy = dup(0);
		stdout_copy = dup(1);
		stderr_copy = dup(2);
		if (stderr_copy < 0 || stdin_copy < 0 || stdout_copy < 0)
			return (perror("dup"), free_cmd_list(lst), exit_free(env));
		close(0);
		close(1);
		close(2);
		builtins_router(
			get_node(lst, CMD, PIPE), count_type_in_lst(lst, ARG, PIPE), env);
		if (dup2(stdin_copy, 0) < 0
			|| dup2(stdout_copy, 1) < 0
			|| dup2(stderr_copy, 2) < 0)
			return (perror("dup2"), free_cmd_list(lst), exit_free(env));
	}
}

int	parsing(char *cmd, t_minish *env)
{
	t_cmd	*lst;

	lst = NULL;
	if (!cmd || cmd[0] == '\0')
		return (g_return_status = 0);
	cmd = ft_strdup(cmd);
	if (!cmd)
		return (-1);
	delete_tab(cmd);
	lst = create_lst_cmd(cmd, lst, env);
	if (!lst)
		return (-1);
	prompt_for_pipe(env, lst, cmd);
	if (cmd)
		free (cmd);
	browse_lst(lst, env);
	env->cmd_lst = lst;
	fork_parsing(lst, env);
	wait(&env->status_parent);
	if (WEXITSTATUS(env->status_parent) || !WEXITSTATUS(env->status_parent))
		g_return_status = WEXITSTATUS(env->status_parent);
	copystd_and_exec_builtins(lst, env);
	return (free_cmd_list(lst), 1);
}
