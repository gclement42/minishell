/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_variable.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaisne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 09:50:48 by gclement          #+#    #+#             */
/*   Updated: 2023/05/03 14:10:24 by jlaisne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

char	*check_if_replace_var_in_str(char *str, char del, t_minish *env)
{
	int		i;

	i = 0;
	while (str[i] && str[i] != del)
	{
		if (str[i] == '$' && (str[i + 1] \
			&& str[i + 1] != '>' && str[i + 1] != '<' \
			&& (ft_isalnum(str[i + 1]) \
			|| str[i + 1] == '?' || str[i + 1] == '\'')))
			str = replace_variable(str, env, &i);
		i++;
	}
	return (str);
}

void	browse_lst(t_cmd *lst, t_minish *env)
{
	while (lst)
	{
		if (lst->type == REDIRECT && !is_here_doc(lst))
			lst = lst->next;
		else
		{
			if (!ft_memcmp(lst->content, "$", ft_strlen(lst->content))
				&& ft_strlen(lst->content) == 1 && lst->marks == SPACES
				&& lst->next && lst->next->marks != SPACES)
				lst->type = S_SPACES;
			else
			{
				if (!(!ft_memcmp(lst->content, "$", ft_strlen(lst->content)) \
					&& ft_strlen(lst->content) == 1 && lst->marks != SPACES)
					&& lst->marks != QUOTE)
					lst->content = check_if_replace_var_in_str(
							lst->content, '\0', env);
				if (is_all_char(lst->content, ' ') && lst->marks == SPACES)
					lst->type = S_SPACES;
			}
		}
		if (lst)
			lst = lst->next;
	}
}
