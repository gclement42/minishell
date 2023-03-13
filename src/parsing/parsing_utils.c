/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gclement <gclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 09:17:44 by gclement          #+#    #+#             */
/*   Updated: 2023/03/13 13:13:41 by gclement         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	check_is_builtins(t_cmd *node, t_minish *env)
{
	int		i;
	size_t	len;

	i = 0;
	while (env->builtins[i])
	{
		len = ft_strlen(node->content);
		if (ft_strncmp(env->builtins[i], node->content, \
			len) == 0 && ft_strlen(env->builtins[i]) == len)
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

int	count_type_in_lst(t_cmd *lst, t_type type)
{
	int	count;

	count = 0;
	while (lst)
	{
		// printf("content = %s\n", lst->content);
		// printf("marks = %d\n", lst->marks);
		// printf("type = %d\n\n", lst->type);
		if (lst->type == type)
			count++;
		lst = lst->next;
	}
	return (count);
}