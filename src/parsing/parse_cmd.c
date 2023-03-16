/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gclement <gclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 17:32:55 by gclement          #+#    #+#             */
/*   Updated: 2023/03/16 16:06:48 by gclement         ###   ########.fr       */
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


t_cmd	*replace_variable(t_cmd *lst, t_minish *env)
{
	char	*new_content;
	int		i;

	while (lst)
	{
		i = 0;
		while (lst->content[i])
		{
			if (lst->content[i] == '$' && lst->marks != QUOTE)
			{
				if (lst->content[i + 1] == '?')
					new_content = ft_itoa(errno);
				else
					new_content = search_key(env->env_list, &lst->content[i + 1]);
				if (new_content)
					lst->content = join_new_content(new_content, lst->content, i);
				if (!lst->content)
					return (NULL);
			}
			i++;
		}
		lst = lst->next;
	}
	return (lst);
}

int	is_all_spaces(char *word)
{
	int	x;

	x = 0;
	while (word[x])
	{
		if (word[x] != ' ')
			return (0);
		x++;
	}
	return (1);
}

void	get_word_with_space(char *word, t_cmd **lst, int is_eol)
{
	char	**split_word;
	int		x;
	char	*tmp;

	x = 0;
	if (ft_strchr(word, ' ') && is_all_spaces(word) == 0)
	{
		split_word = ft_split(word, ' ');
		while (split_word[x])
		{
			if (word[ft_strlen(word) - 1] == ' ' && !split_word[x + 1] && is_eol == 0)
			{
				tmp = ft_strjoin(split_word[x], " ");
				new_node_cmd(tmp, SPACES, ARG, lst);
				return ;
			}
			new_node_cmd(split_word[x], SPACES, ARG, lst);
			x++;
		}
		return ;
	}
	if (is_all_spaces(word) == 0)
		new_node_cmd(word, SPACES, ARG, lst);
}
