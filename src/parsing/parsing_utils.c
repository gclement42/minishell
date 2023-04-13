/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gclement <gclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 09:17:44 by gclement          #+#    #+#             */
/*   Updated: 2023/04/13 13:51:43 by gclement         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	check_is_builtins(t_cmd *node, t_minish *env)
{
	int		i;
	size_t	len;

	i = 0;
	if (!node)
		return (0);
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
	while (cmd[i] && cmd[i] != c)
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
	int		i;

	i = 0;
	if (key[0] == '?')
		return (ft_itoa(g_return_status));
	while (ft_isalnum(key[i]))
		i++;
	while (lst_env && key[0] != '\0')
	{
		if (ft_memcmp(lst_env->key, key, ft_strlen(lst_env->key)) == 0
			&& (size_t)i == ft_strlen(lst_env->key))
			return (lst_env->content);
		lst_env = lst_env->next;
	}
	return (NULL);
}

int	is_special_char(char c)
{
	if (c == '_')
		return (0);
	if ((((c >= 33 && c <= 47) || (c >= 58 && c <= 63) \
		|| (c >= 91 && c <= 96) || (c >= 123 && c <= 126)) \
		|| c == '@' || (c >= '0' && c <= '9')) && (c != '\'' || c != '"'))
		return (1);
	return (0);
}

