/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gclement <gclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 09:17:44 by gclement          #+#    #+#             */
/*   Updated: 2023/02/17 09:45:36 by gclement         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**set_argxec(char **cmd)
{
	char	**argxec;
	int		x;

	x = 0;
	while (cmd[x])
		x++;
	argxec = malloc((x + 1) * sizeof(char *));
	if (!argxec)
		exit (EXIT_FAILURE);
	x = 0;
	while (cmd[x])
	{
		argxec[x] = cmd[x];
		x++;
	}
	argxec[x] = NULL;
	return (argxec);
}

int	check_is_builtins(const char *cmd, t_minish env)
{
	int	i;

	i = 0;
	while (env.builtins[i])
	{
		if (ft_strncmp(env.builtins[i], cmd, ft_strlen(env.builtins[i])) == 0)
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
