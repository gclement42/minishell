/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gclement <gclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 17:32:55 by gclement          #+#    #+#             */
/*   Updated: 2023/05/03 13:56:22 by jlaisne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	char	**count_and_malloc(t_cmd *lst, int *len)
{
	t_cmd	*tmp;
	char	**arr_exec;

	tmp = lst;
	tmp = tmp->next;
	while (tmp && tmp->type != PIPE)
	{
		if (tmp->type == S_SPACES)
			tmp = tmp->next;
		else
		{
			if (tmp->type == ARG || tmp->type == OPT)
				*len += 1;
			tmp = tmp->next;
		}
	}
	arr_exec = malloc((*len + 1) * sizeof(char *));
	if (!arr_exec)
		return (NULL);
	return (arr_exec);
}

char	**create_arr_exec(t_cmd *cmd)
{
	char	**arr_exec;
	int		len;
	int		x;

	len = 1;
	x = 0;
	arr_exec = count_and_malloc(cmd, &len);
	if (!arr_exec)
		return (NULL);
	while (x < len)
	{
		if (cmd->type != S_SPACES && \
		(cmd->type == OPT || cmd->type == ARG || cmd->type == CMD))
		{
			arr_exec[x] = ft_strdup(cmd->content);
			if (!arr_exec[x])
				return (free_2d_array(arr_exec));
			x++;
		}
		cmd = cmd->next;
	}
	return (arr_exec[x] = NULL, arr_exec);
}

int	is_all_char(char *word, char c)
{
	int	x;

	x = 0;
	while (word[x])
	{
		if (word[x] != c)
			return (0);
		x++;
	}
	return (1);
}

t_cmd	*prompt_for_pipe(t_minish *env, t_cmd *lst, char *cmd)
{
	t_cmd	*last;
	char	*prompt;

	last = cmd_lst_last(&lst);
	if (((!ft_memcmp(last->content, "|", 1) \
		&& last->marks == SPACES) \
		|| cmd[ft_strlen(cmd) - 1] == '|') && last->type != CMD)
	{
		prompt = readline(">");
		if (!prompt || str_isascii(prompt) == 0)
			return (ft_putstr_fd(\
				"minishell: syntax error: unexpected end of file\n", 2), \
				g_return_status = 2, \
					free(cmd), free_cmd_list(lst), exit_env(env), NULL);
		if (last->type != ARG)
			new_node_cmd("|", SPACES, PIPE, &lst);
		else
			last->type = PIPE;
		lst = create_lst_cmd(prompt, lst, env);
	}
	return (lst);
}
