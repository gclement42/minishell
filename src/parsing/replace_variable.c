/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_variable.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gclement <gclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 09:50:48 by gclement          #+#    #+#             */
/*   Updated: 2023/03/23 11:57:47 by gclement         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char *join_content_next_var(char *content, char *var_content)
{
	char	*eow;
	char	*join_content;
	int		start;

	start = 0;
	while (content[start] != '$')
		start++;
	start++;
	while (ft_isalpha(content[start]) == 1 || content[start] == '?')
		start++;
	eow = ft_substr(content, start, (ft_strlen(content)) - start);
	if (!eow)
		return (NULL);
	join_content = ft_strjoin(var_content, eow);
	return (free(var_content), free(eow), join_content);	
}

static	char *join_new_content(char *new_content, char *content, int size)
{
	char	*str_begin;
	char	*str;
	
	if (size > 0)
	{
		str_begin = malloc((size + 1) * sizeof(char));
		if (!str_begin)
			return (NULL);
		str_begin = ft_memcpy(str_begin, content, size);
		str_begin[size] = '\0';
		str = ft_strjoin(str_begin, new_content);
		str = join_content_next_var(content, str);
		return (str);
	}
	else
	{
		free(content);
		if (new_content)
			content = new_content;
		else
			content = " ";
	}
	return (content);
}

char	*replace_variable(char *str, t_minish *env)
{
	char	*new_content;
	int		i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '$')
		{
			if (str[i - 1] == '\\')
				new_content = ft_strdup(&str[i]);
			else if (str[i + 1] == '?')
				new_content = ft_itoa(return_status);
			else
				new_content = search_key(env->env_list, &str[i + 1]);
			if (str[i - 1] == '\\')
				str = new_content;
			else if (new_content)
				str = join_new_content(new_content, str, i);
			if (!str)
				return (NULL);
		}
	}
	return (str);
}
t_cmd *check_if_replace_var(t_cmd *lst, t_minish *env)
{
	while (lst)
	{
		if (lst->marks != QUOTE)
			replace_variable(lst->content, env);
		lst = lst->next;
	}
	return (lst);
}