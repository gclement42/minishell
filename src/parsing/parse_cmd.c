/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gclement <gclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 17:32:55 by gclement          #+#    #+#             */
/*   Updated: 2023/04/20 11:29:10 by gclement         ###   ########.fr       */
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

int	check_if_unexpected_token(t_cmd *node, t_minish *env)
{
	int	i;

	i = 0;
	while (node && node->type != CMD)
		node = node->next;
	while (node->content && (ft_isalnum(node->content[i]) || \
		(node->content[i] >= 33 && node->content[i] <= 47) \
		|| node->content[i] == ' ' || node->content[i] == ')' \
		|| node->content[i] == '}'))
		i++;
	if (node->content[i] || node->type == PIPE)
	{
		g_return_status = 2;
		msg_unexpected_token(node->content[i]);
		free_cmd_list(env->cmd_lst);
		if (env->env_tab)
			free_2d_array(env->env_tab);
		if (env->var->env_cmd)
			free_2d_array(env->var->env_cmd);
		if (env->var->pipefds)
			free(env->var->pipefds);
		exit_free(env);
	}
	return (1);
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

t_cmd	*prompt_for_pipe(t_cmd *lst, char *cmd)
{
	t_cmd	*last;
	char	*prompt;

	last = cmd_lst_last(&lst);
	if (last->type == CMD && ft_memcmp(last->content, \
		"|", ft_strlen(last->content)) \
		&& cmd[ft_strlen(cmd) - 1] == '|')
	{
		prompt = readline(">");
		new_node_cmd("|", SPACES, PIPE, &lst);
		lst = create_lst_cmd(prompt, lst);
	}
	return (lst);
}
