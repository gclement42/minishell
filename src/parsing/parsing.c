/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaisne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 15:05:17 by gclement          #+#    #+#             */
/*   Updated: 2023/04/12 10:52:41 by jlaisne          ###   ########.fr       */
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
		parse_router(cmd, &i, &start, lst);
		if (!cmd[i])
			break ;
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

static	t_cmd	*create_lst_cmd(char *cmd, int *b)
{
	char	**split_by_pipe;
	t_cmd	*lst;
	int		i;

	i = 0;
	lst = NULL;
	if (is_all_char(cmd, '|') || cmd[0] == '|')
		return (g_return_status = 2, ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", 2), NULL);
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
	if (*b == 1)
		free (cmd);
	return (free_2d_array(split_by_pipe), lst);
}

void	display_lst(t_cmd *lst)
{
	(void) lst;
	while (lst)
	{
		printf("content = %s\n", lst->content);
		printf("type = %d\n", lst->type);
		printf("marks = %d\n", lst->marks);
		lst = lst->next;
	}
	printf("-------------------------------------------------------\n");
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

static void	copystd_and_exec_builtins(t_cmd *arg, t_cmd *lst, t_minish *env)
{
	int		stdin_copy;
	int		stdout_copy;
	int		stderr_copy;

	if (!arg && ft_memcmp(lst->content, "exit", 4))
		return ;
	if (check_if_unexpected_token(lst, env) == 0)
		return ;
	if (lst && count_type_in_lst(arg, PIPE) == 0)
	{
		stdin_copy = dup(0);
		stdout_copy = dup(1);
		stderr_copy = dup(2);
		close(0);
		close(1);
		close(2);
		builtins_router(get_node(lst, CMD, PIPE), count_type_in_lst(lst, ARG), env);
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

	b = 0;
	if (!cmd || cmd[0] == '\0')
		return (g_return_status = 0);
	cmd = check_if_replace_var(cmd, env, 1, &b);
	lst = create_lst_cmd(cmd, &b);
	if (!lst)
		return (-1);
	env->cmd_lst = lst;
	cmd_node = get_node(lst, CMD, PIPE);
	if (cmd_node)
		cmd_node->content = remove_quote(cmd_node->content);
	fork_parsing(lst, env);
	wait(&env->var->status);
	if (WEXITSTATUS(env->var->status))
		g_return_status = WEXITSTATUS(env->var->status);
	copystd_and_exec_builtins(get_node(lst, ARG, PIPE), lst, env);
	return (free_cmd_list(lst), 1);
}
