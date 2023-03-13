/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gclement <gclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 17:32:55 by gclement          #+#    #+#             */
/*   Updated: 2023/03/13 12:50:07 by gclement         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	char *join_new_content(char *new_content, char *content, int size)
{
	char	*str;
	
	if (size > 0)
	{
		str = malloc((size + 1) * sizeof(char));
		if (!str)
			return (NULL);
		str = ft_memcpy(str, content, size);
		str[size] = '\0';
		free(content);
		content = ft_strjoin(str, new_content);
		if (!content)
			return (NULL);
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
				new_content = search_key(env->env_list, &lst->content[i + 1]);
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

static int	is_all_spaces(char *word)
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
	new_node_cmd(word, SPACES, ARG, lst);
}

void	search_if_redirect(t_pipex *var, t_cmd *lst, int pipe_fd[2])
{
	while (lst)
	{
		if (lst->type == REDIRECT)
		{
			if (ft_memcmp("<", lst->content, ft_strlen(lst->content)) == 0)
				open_fd_in(var, lst->next->content);
			else if (ft_memcmp("<<", lst->content, ft_strlen(lst->content)) == 0)
				create_heredoc(lst, pipe_fd);
			if (ft_memcmp(">", lst->content, ft_strlen(lst->content)) == 0)
				open_fd_out(var, lst->next->content, 0);
			else if (ft_memcmp(">>", lst->content, ft_strlen(lst->content)) == 0)
				open_fd_out(var, lst->next->content, 1);
		}
		lst = lst->next;
	}
}