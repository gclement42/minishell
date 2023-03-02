/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaisne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 09:17:44 by gclement          #+#    #+#             */
/*   Updated: 2023/03/02 14:37:32 by jlaisne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"


int	check_is_builtins(t_cmd *node, t_minish *env)
{
	int	i;

	i = 0;
	while (env->builtins[i])
	{
		if (ft_strncmp(env->builtins[i], node->content, \
			ft_strlen(env->builtins[i])) == 0)
			return (1);
		i++;
	}
	return (0);
}

size_t	count_len(char *cmd, char c)
{
	size_t	i;

	i = 1;
	while (cmd[i] != c && cmd[i])
		i++;
	return (i);
}

t_marks	get_marks(char c)
{
	if (c == '\'')
		return (QUOTE);
	if (c == '"')
		return (DQUOTE);
	else
		return (SPACES);
}

char	*prompt_for_quote_termination(char *cmd, char c)
{
	char	*prompt;
	char	*content;
	char	*cmd_join;
	char	*tmp;
	int		i;

	prompt = "dquote>";
	if (c == '\'')
		prompt = "quote>";
	content = readline(prompt);
	cmd_join = ft_strjoin(cmd, content);
	i = ft_strlen(cmd_join);
	while (cmd_join[i - 1] != c)
	{
		free(content);
		content = readline(prompt);
		tmp = ft_strjoin(cmd_join, content);
		free(cmd_join);
		cmd_join = tmp;
		i = ft_strlen(cmd_join);
	}
	free (content);
	free (cmd);
	return (cmd_join);
}

char	*search_key(t_env *lst_env, char *key)
{
	char	*res;

	res = NULL;
	while (lst_env)
	{
		res = ft_strnstr(lst_env->key, key, ft_strlen(key));
		if (res && !res[ft_strlen(key) + 1])
			return (lst_env->content);
		lst_env = lst_env->next;
	}
	return (NULL);
}