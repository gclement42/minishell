/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_is.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaisne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 10:21:11 by gclement          #+#    #+#             */
/*   Updated: 2023/05/04 11:53:13 by jlaisne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_is_valid_identifier(char *str, char *cmd)
{
	int	i;

	i = 0;
	if (!str[i] || is_special_char(str[i]) || \
		((str[i] != '$' ) && str[i] == '/' && str[i] == ' ' && \
		(str[i] == '=' || is_special_char(str[i]))) || str_isdigit(str) == 1)
	{
		ft_printf("minishell : %s : `%s' : not a valid identifier\n", \
			cmd, str);
		return (g_return_status = 1, 0);
	}
	i++;
	while (str[i])
	{
		if ((ft_isalnum(str[i]) == 0 && is_special_char(str[i]))
			|| str[i] == '/' || str[i] == ' ')
		{
			ft_printf("minishell : %s : `%s' : not a valid identifier\n", \
			cmd, str);
			return (g_return_status = 1, 0);
		}
		i++;
	}
	return (1);
}

int	check_is_builtins(t_cmd *node, t_minish *env)
{
	int		i;
	size_t	len;

	i = 0;
	if (!node)
		return (0);
	while (env->builtins[i])
	{
		len = ft_strlen(node->content);
		if (ft_strncmp(env->builtins[i], node->content, \
			len) == 0 && ft_strlen(env->builtins[i]) == len)
			return (1);
		i++;
	}
	return (0);
}

int	check_if_unexpected_token(t_cmd *node, t_minish *env)
{
	int	i;

	i = 0;
	while (node && node->type != CMD)
		node = node->next;
	while (node->content && (ft_isalnum(node->content[i]) || \
		(node->content[i] >= 33 && node->content[i] <= 47) \
		|| node->content[i] == ' ' || node->content[i] == '\t' \
		|| node->content[i] == ')' \
		|| node->content[i] == '}'))
		i++;
	if (node->content[i] || node->type == PIPE)
	{
		g_return_status = 2;
		msg_unexpected_token(node->content[i]);
		free_cmd_list(env->cmd_lst);
		if (env->env_tab)
			free_2d_array(env->env_tab);
		if (env->pipex->env_cmd)
			free_2d_array(env->pipex->env_cmd);
		if (env->pipex->pipefds)
			free(env->pipex->pipefds);
		exit_free(env);
	}
	return (1);
}
