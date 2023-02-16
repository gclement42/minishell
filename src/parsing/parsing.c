/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gclement <gclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 15:05:17 by gclement          #+#    #+#             */
/*   Updated: 2023/02/16 10:27:04 by gclement         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	size_t	count_len(char *cmd, char c)
{
	size_t	i;

	i = 1;
	while (cmd[i] != c && cmd[i])
		i++;
	return (i);
}

char	**create_2d_arr(char *cmd)
{
	size_t	i;
	int		len;
	char	**arr;
	size_t	start;

	i = 0;
	len = 0;
	start = 0;
	while (cmd[i])
	{
		if (cmd[i] == '"' || cmd[i] == '\'')
		{
			if (start < i)
				len++;
			i += count_len(&cmd[i], cmd[i]);
			len++;
			start = i;
		}
		i++;
	}
	arr = malloc((len + 1) * sizeof(char *));
	return (arr);
}

char	*malloc_line(int *i, char *cmd, size_t *start)
{
	size_t	len;
	char	*arg;

	len = 0;
	len = count_len(&cmd[*i], cmd[*i]);
	*i += 1;
	arg = ft_substr(cmd, *i, --len);
	*i += len;
	*start = *i + 1;
	return (arg);
}

static char	**parsing_true(char *cmd)
{
	int		i;
	int		y;
	size_t	start;
	char	**arg;

	i = 0;
	y = 0;
	start = 0;
	arg = create_2d_arr(cmd);
	while (cmd[i])
	{
		if (cmd[i] == '"' || cmd[i] == '\'')
		{
			if (start < (size_t)i)
				arg[y++] = ft_substr(cmd, start, i - start);
			arg[y] = malloc_line(&i, cmd, &start);
			if (!arg[y++])
				free_2d_array(arg);
		}	
		i++;
	}
	if (start < (size_t)i)
		arg[y++] = ft_substr(cmd, start, i - start);
	return (arg[y] = NULL, arg);
}

char	**parsing(char *cmd, t_minish env)
{
	char	**split_cmd;
	//char	**arg_exec;

	(void) env;
	split_cmd = parsing_true(cmd);
	if (!split_cmd)
		exit (EXIT_FAILURE);
	int i = 0;
	while (split_cmd[i])
	{
		printf("%s\n", split_cmd[i]);
		i++;
	}
	// arg_exec = set_argxec(split_cmd);
	// if (!arg_exec)
	// 	free_2d_array(arg_exec);
	// (void) env;
	// if (check_is_builtins(split_cmd[0], env) == 1)
	// 	builtins_parsing(arg_exec, count_nb_arg(arg_exec));
	return (split_cmd);
}

