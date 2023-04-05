/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_variable.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gclement <gclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 09:50:48 by gclement          #+#    #+#             */
/*   Updated: 2023/04/05 10:45:41 by gclement         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*join_content_next_var(char *content, char *var_content)
{
	char	*eow;
	char	*join_content;
	int		s;

	s = 0;
	while (content[s] && content[s] != '$')
		s++;
	s++;
	if (content[s] && (ft_isdigit(content[s]) || is_special_char(content[s])))
		s++;
	else
		while (content[s] && ft_isalnum(content[s])
			&& content[s] != '?' && content[s] != '"'
			&& content[s] != '\'')
			s++;
	if (content[s] && content[s] == '?')
		if (content[s - 1] && content[s - 1] == '$')
			s++;
	eow = ft_substr(content, s, (ft_strlen(content)) - s);
	if (!eow)
		return (NULL);
	join_content = ft_strjoin(var_content, eow);
	return (free(var_content), free(eow), join_content);
}

static	char	*join_new_content(char *new_content, char *content, \
	int size, int *b)
{
	char	*str_begin;
	char	*str;

	*b = 1;
	str_begin = malloc((size + 1) * sizeof(char));
	if (!str_begin)
		return (NULL);
	str_begin = ft_memcpy(str_begin, content, size);
	str_begin[size] = '\0';
	if (new_content)
		str = ft_strjoin(str_begin, new_content);
	else
		str = ft_strdup(str_begin);
	if (!str)
		return (NULL);
	str = join_content_next_var(content, str);
	return (free(str_begin), str);
}

void	skip_quote(int *i, char *str, char del)
{	
	*i += 1;
	while (str[*i] && str[*i] != del)
		*i += 1;
}

char	*replace_variable(char *str, t_minish *env, int *i, int *b)
{
	char	*new_content;
	int		bools;

	bools = 0;
	if (str[*i + 1] == '?')
	{
		new_content = ft_itoa(return_status);
		bools = 1;
	}
	else
		new_content = search_key(env->env_list, &str[*i + 1]);
	str = join_new_content(new_content, str, *i, b);
	if (!str)
		return (NULL);
	if (new_content && ft_strchr(new_content, '$'))
		*i += ft_strlen(new_content);
	if (str[*i] != '$' || !new_content)
		*i -= 1;
	if (bools == 1)
		free (new_content);
	return (str);
}

char	*check_if_replace_var(char *str, t_minish *env, int bskip_quote, int *b)
{
	int		i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '\'' && bskip_quote == 1)
			skip_quote(&i, str, '\'');
		if (!str[i])
			break ;
		if (str[i] == '$' && (str[i + 1]
				&& (ft_isalnum(str[i + 1]) || is_special_char(str[i + 1])
					|| str[i + 1] == '?' || str[i + 1] == '"'
					|| str[i + 1] == '\'')))
			str = replace_variable(str, env, &i, b);
	}
	return (str);
}
