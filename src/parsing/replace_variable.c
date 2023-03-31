/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_variable.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gclement <gclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 09:50:48 by gclement          #+#    #+#             */
/*   Updated: 2023/03/30 19:50:59 by gclement         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*join_content_next_var(char *content, char *var_content)
{
	char	*eow;
	char	*join_content;
	int		start;

	start = 0;
	while (content[start] != '$')
		start++;
	start++;
	if (ft_isdigit(content[start]) || is_special_char(content[start]))
		start++;
	else
		while (content[start] && ft_isalnum(content[start]) && \
			content[start] != '?' \
		&& content[start] != '"' && content[start] != '\'')
			start++;
	if (content[start] == '?')
		if (content[start - 1] && content[start - 1] == '$')
			start++;
	eow = ft_substr(content, start, (ft_strlen(content)) - start);
	if (!eow)
		return (NULL);
	join_content = ft_strjoin(var_content, eow);
	return (free(var_content), free(eow), join_content);
}

static	char	*join_new_content(char *new_content, char *content, int size)
{
	char	*str_begin;
	char	*str;

	str_begin = malloc((size + 1) * sizeof(char));
	if (!str_begin)
		return (NULL);
	str_begin = ft_memcpy(str_begin, content, size);
	str_begin[size] = '\0';
	if (new_content)
		str = ft_strjoin(str_begin, new_content);
	else
		str = str_begin;
	str = join_content_next_var(content, str);
	return (str);
}

void	skip_quote(int *i, char *str, char del)
{	
	*i += 1;
	while (str[*i] && str[*i] != del)
		*i += 1;
}

char	*replace_variable(char *str, t_minish *env, int b_skip_quote)
{
	char	*new_content;
	int		i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '\'' && b_skip_quote == 1)
			skip_quote(&i, str, '\'');
		if (str[i] == '$' && (str[i + 1] && (ft_isalnum(str[i + 1]) || is_special_char(str[i + 1]) \
		|| str[i + 1] == '?' || str[i + 1] == '"' || str[i + 1] == '\'')))
		{
			if (str[i + 1] == '?')
				new_content = ft_itoa(return_status);
			else
				new_content = search_key(env->env_list, &str[i + 1]);
			str = join_new_content(new_content, str, i);
			if (new_content && ft_strchr(new_content, '$'))
				i += ft_strlen(new_content);
			if (str[i] != '$' || new_content)
				i--;
			if (!str)
				return (NULL);
		}
	}
	return (str);
}

t_cmd	*check_if_replace_var(t_cmd *lst, t_minish *env)
{
	//display_lst(lst);
	while (lst)
	{
		if (lst->marks != QUOTE)
		{
			if (lst->type == CMD)
				lst->content = replace_variable(lst->content, env, 1);
			else
				lst->content = replace_variable(lst->content, env, 0);
		}
		if (lst->type == CMD)
			lst->content = remove_quote(lst->content);
		lst = lst->next;
	}
	return (lst);
}
