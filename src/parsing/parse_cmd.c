/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gclement <gclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 17:32:55 by gclement          #+#    #+#             */
/*   Updated: 2023/03/09 13:20:39 by gclement         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*replace_variable(t_cmd *lst, t_minish *env)
{
	char	*new_content;

	while (lst)
	{
		if (lst->content[0] == '$' && lst->marks != QUOTE)
		{
			new_content = search_key(env->env_list, &lst->content[1]);
			free(lst->content);
			if (new_content)
				lst->content = new_content;
			else
				lst->content = " ";
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

void	get_word_with_space(char *word, t_cmd **lst)
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
			if (word[ft_strlen(word) - 1] == ' ' && !split_word[x + 1])
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
}

/* Manque les retour a la ligne */
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

void	search_if_redirect(t_pipex *var, t_cmd *lst, int pipe_fd[2])
{
	while (lst)
	{
		if (lst->type == REDIRECT)
		{
			if (ft_memcmp("<<", lst->content, ft_strlen(lst->content)) == 0)
				create_heredoc(var ,lst, pipe_fd);
			if (ft_memcmp("<", lst->content, ft_strlen(lst->content)) == 0)
				open_fd_in(var, lst->next->content);
			if (ft_memcmp(">", lst->content, ft_strlen(lst->content)) == 0)
				open_fd_out(var, lst->next->content, 0);
			if (ft_memcmp(">>", lst->content, ft_strlen(lst->content)) == 0)
				open_fd_out(var, lst->next->content, 1);
		}
		lst = lst->next;
	}
}