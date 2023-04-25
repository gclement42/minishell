/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_variable.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gclement <gclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 09:50:48 by gclement          #+#    #+#             */
/*   Updated: 2023/04/25 14:23:35 by gclement         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static char	*join_content_next_var(char *content, char *var_content,
// 	char *n_c, int s)
// {
// 	char	*eow;
// 	char	*join_content;

// 	if (n_c)
// 		s++;
// 	if (content[s] == '$' || !is_special_char(content[s]))
// 		s++;
// 	else
// 	{
// 		while (content[s] && 
// 		(ft_isalnum(content[s]) || !is_special_char(content[s])) 
// 		&& content[s] != '?' && (content[s] != '\'' && content[s] != '"' 
// 		&& content[s] != '$') && content[s] != '<' && content[s] != '>')
// 			s++;
// 	}
// 	printf("apres s = %c && s = %d\n", content[s], s);
// 	eow = ft_substr(content, s, (ft_strlen(content) - s));
// 	if (!eow)
// 		return (NULL);
// 	join_content = ft_strjoin(var_content, eow);
// 	printf("content = %s\neow = %s\njoin = %s\n\n", content, eow, join_content);
// 	return (free(var_content), free(eow), join_content);
// }

static char	*join_content_next_var(char *content, char *var_content,
	char *n_c, int s)
{
	char	*eow;
	char	*join_content;

	(void) n_c;
	s++;
	if (content[s] && (ft_isdigit(content[s])))
		s++;
	else
		while (content[s] && ft_isalnum(content[s]))
			s++;
	if (content[s] && content[s] == '?')
		if (content[s - 1] && content[s - 1] == '$')
			s++;
	eow = ft_substr(content, s, (ft_strlen(content) - s));
	if (!eow)
		return (NULL);
	join_content = ft_strjoin(var_content, eow);
	return (free(var_content), free(eow), join_content);
}

static	char	*join_new_content(char *new_content, char *content, \
	int size)
{
	char	*str_begin;
	char	*str;

	str_begin = malloc((size + 1) * sizeof(char));
	if (!str_begin)
		return (free(content), NULL);
	str_begin = ft_memcpy(str_begin, content, size);
	str_begin[size] = '\0';
	if (new_content)
		str = ft_strjoin(str_begin, new_content);
	else
		str = ft_strdup(str_begin);
	if (!str)
		return (free(content), free(str_begin), NULL);
	str = join_content_next_var(content, str, new_content, size);
	return (free(str_begin), free(content), str);
}

void	skip_quote(int *i, char *str, char del)
{	
	*i += 1;
	while (str[*i] && str[*i] != del)
		*i += 1;
}

char	*replace_variable(char *str, t_minish *env, int *i)
{
	char	*new_content;
	int		bools;

	bools = 0;
	if (str[*i + 1] == '?')
		bools = 1;
	new_content = search_key(env->env_list, &str[*i + 1]);
	str = join_new_content(new_content, str, *i);
	if (!str)
		return (free(str), exit_env(env), NULL);
	if (new_content && ft_strchr(new_content, '$'))
		*i += ft_strlen(new_content);
	if (str[*i] != '$' || !new_content)
		*i -= 1;
	if (bools == 1)
		free (new_content);
	return (str);
}

char	*check_if_replace_var(char *str, t_minish *env, int bskip_quote)
{
	int		i;
	int		b_dq;

	i = -1;
	b_dq = 0;
	str = ft_strdup(str);
	if (!str)
		return (NULL);
	while (str[++i])
	{
		if (str[i] == '"' && bskip_quote == 1 && b_dq == 0)
			b_dq = 1;
		else if (str[i] == '"' && b_dq == 1)
			b_dq = 0;
		if (str[i] == '\'' && bskip_quote == 1 && b_dq == 0)
			skip_quote(&i, str, '\'');
		if (!str[i])
			break ;
		if (str[i] == '$' && (str[i + 1] \
			&& str[i + 1] != '>' && str[i + 1] != '<' \
			&& (ft_isalnum(str[i + 1]) || is_special_char(str[i + 1]) \
			|| str[i + 1] == '?' || str[i + 1] == '\'')))
			str = replace_variable(str, env, &i);
	}
	return (str);
}
