/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_parsing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaisne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 10:37:47 by gclement          #+#    #+#             */
/*   Updated: 2023/04/12 10:49:05 by jlaisne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	builtins_router(t_cmd *cmd_node, int argc, t_minish *var)
{
	t_cmd	*arg_node;
	t_env	*env_lst;
	size_t	cmd_len;

	env_lst = NULL;
	arg_node = get_node(cmd_node, ARG, PIPE);
	cmd_len = ft_strlen(cmd_node->content);
	if (ft_memcmp(cmd_node->content, "export", cmd_len) == 0)
		env_lst = export_variable_parsing(cmd_node, cmd_node->content);
	if (ft_memcmp(cmd_node->content, "cd", cmd_len) == 0 && cmd_len == 2)
		cd_parsing(arg_node, argc, var);
	if (ft_memcmp(cmd_node->content, "pwd", cmd_len) == 0 && cmd_len == 3)
		pwd_parsing(cmd_node, var);
	if (ft_memcmp(cmd_node->content, "env", cmd_len) == 0 && cmd_len == 3)
		parsing_env(var, cmd_node);
	if (ft_memcmp(cmd_node->content, "unset", cmd_len) == 0 && cmd_len == 5)
		unset_parsing(var, cmd_node);
	if (ft_memcmp(cmd_node->content, "export", cmd_len) == 0 && cmd_len == 6)
		export_parsing(var, argc, env_lst, arg_node);
	if (ft_memcmp(cmd_node->content, "echo", cmd_len) == 0 && cmd_len == 4)
		echo_parsing(cmd_node, var);
	if (ft_memcmp(cmd_node->content, "exit", cmd_len) == 0 && cmd_len == 4)
	{
		ft_putstr_fd("1", 2);
		exit_parsing(cmd_node, var);
	}
}

int	check_is_valid_identifier(char *str, char *cmd)
{
	int	i;

	i = 0;
	if (!str[i] || ((str[i] != '$' && str[i] != ' ') && str[i] != '/' && \
		(str[i] == '=' || is_special_char(str[i]))))
	{
		printf("minishell : %s : `%s' : not a valid identifier\n", \
			cmd, str);
		return (g_return_status = 1, 0);
	}
	i++;
	while (str[i])
	{
		if ((ft_isalnum(str[i]) == 0 && is_special_char(str[i]))
			&& str[i] != '/' && \
		str[i] != '=' && str[i] != ' ' && str[i] != '$')
		{
			printf("minishell : %s : `%s' : not a valid identifier\n", \
			cmd, str);
			return (g_return_status = 1, 0);
		}
		i++;
	}
	return (1);
}

static	t_env	*create_tmp_lst_env(char *arg)
{
	t_env	*new;
	char	**split_key_value;
	int		i;

	i = 0;
	if (!arg)
		return (NULL);
	if (arg[0] == '=' || !ft_strchr(arg, '='))
		new = ft_lstnew_env(arg, "");
	else
	{
		split_key_value = split_env_var(arg);
		if (!split_key_value)
			return (NULL);
		new = ft_lstnew_env(split_key_value[0], split_key_value[1]);
		free_2d_array(split_key_value);
	}
	if (!new)
		return (NULL);
	i++;
	return (new);
}

t_env	*create_export_lst(t_env *env_lst, t_cmd *lst, char *cmd_name)
{
	char	*tmp;
	t_env	*new;

	if (lst->next && lst->next->type == ARG && \
		!ft_strchr(lst->content, ' '))
	{
		tmp = join_all_arg(lst, 1);
		free (lst->content);
		lst->content = tmp;
		new = create_tmp_lst_env(lst->content);
		while (lst && lst->type != S_SPACES)
			lst = lst->next;
	}
	else
		new = create_tmp_lst_env(lst->content);
	if (!new)
		return (NULL);
	if (ft_strnstr(cmd_name, "export", 6) != 0 && new->key == NULL)
		free (new);
	else
		ft_lstadd_back_env(&env_lst, new);
	return (env_lst);
}

t_env	*export_variable_parsing(t_cmd *lst, char *cmd_name)
{
	t_env	*env_lst;

	env_lst = NULL;
	while (lst && lst->type != PIPE)
	{
		if (lst->type == OPT)
			return (msg_invalid_opt(lst->content, cmd_name, 1), NULL);
		if (lst->type == ARG)
			env_lst = create_export_lst(env_lst, lst, cmd_name);
		if (lst)
			lst = lst->next;
	}
	return (env_lst);
}
