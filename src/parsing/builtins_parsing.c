/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_parsing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gclement <gclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 10:37:47 by gclement          #+#    #+#             */
/*   Updated: 2023/04/03 15:17:49 by gclement         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	builtins_router(t_cmd *lst, int argc, t_minish *var)
{
	t_cmd	*cmd_node;
	t_cmd	*arg_node;
	t_env	*env_lst;
	size_t	cmd_len;

	env_lst = NULL;
	cmd_node = get_node(lst, CMD, PIPE);
	arg_node = get_node(lst, ARG, PIPE);
	cmd_len = ft_strlen(cmd_node->content);
	if (ft_memcmp(cmd_node->content, "export", cmd_len) == 0)
		env_lst = export_variable_parsing(lst, cmd_node->content);
	if (ft_memcmp(cmd_node->content, "cd", cmd_len) == 0 && cmd_len == 2)
		cd_parsing(arg_node, argc, var);
	if (ft_memcmp(cmd_node->content, "pwd", cmd_len) == 0 && cmd_len == 3)
		pwd_parsing(cmd_node);
	if (ft_memcmp(cmd_node->content, "env", cmd_len) == 0 && cmd_len == 3)
		parsing_env(var, cmd_node);
	if (ft_memcmp(cmd_node->content, "unset", cmd_len) == 0 && cmd_len == 5)
		unset_parsing(var, arg_node);
	if (ft_memcmp(cmd_node->content, "export", cmd_len) == 0 && cmd_len == 6)
		export_parsing(var, argc, env_lst, arg_node);
	if (ft_memcmp(cmd_node->content, "echo", cmd_len) == 0 && cmd_len == 4)
		echo_parsing(cmd_node);
	if (ft_memcmp(cmd_node->content, "exit", cmd_len) == 0 && cmd_len == 4)
		exit_parsing(cmd_node, var);

}

int	is_special_char(char c)
{
	if (((c >= 33 && c <= 47) || (c >= 58 && c <= 63)
		|| (c >= 91 && c <= 96) || (c >= 123 && c <= 126)) || c == '@')
		return (1);
	return (0);
}

int	check_is_valid_identifier(char *str, char *cmd)
{
	int	i;

	i = 0;
	if (!str[i] || ((str[i] != '$' && str[i] != ' ') && str[i] != '/' &&\
		(!ft_isalpha(str[i]) || str[i] == '=' || is_special_char(str[i]))))
	{
		printf("minishell : %s : `%s' : not a valid identifier\n", \
			cmd, str);
		return (return_status = 1, 0);
	}
	i++;
	while (str[i])
	{
		if ((ft_isalnum(str[i]) == 0 && is_special_char(str[i])) && str[i] != '/' && \
		str[i] != '=' && str[i] != ' ' && str[i] != '$')
		{
			printf("minishell : %s : `%s' : not a valid identifier\n", \
			cmd, str);
			return (return_status = 1, 0);
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
	if (arg[0] == '=' || !ft_strchr(arg, '='))
		new = ft_lstnew_env(arg, NULL);
	else
	{
		split_key_value = split_env_var(arg);
		if (!split_key_value)
			return (NULL);
		new = ft_lstnew_env(split_key_value[0], split_key_value[1]);
	}
	if (!new)
		return (NULL);
	i++;
	return (new);
}

t_env	*export_variable_parsing(t_cmd *lst, char *cmd_name)
{
	t_env	*env_lst;
	t_env	*new;

	env_lst = NULL;
	while (lst && lst->type != PIPE)
	{
		if (lst->type == OPT)
			return (msg_invalid_opt(lst->content, cmd_name), NULL);
		if (lst->type == ARG)
		{
			if (lst->next && lst->next->type == ARG && !ft_strchr(lst->content, ' '))
				lst->content = join_all_arg(lst, 1);
			new = create_tmp_lst_env(lst->content);
			if (!new)
				return (NULL);
			if (ft_strnstr(cmd_name, "export", 6) != 0 && new->key == NULL)
				free (new);
			else
				ft_lstadd_back_env(&env_lst, new);
			while (lst->next && lst->type != S_SPACES)
				lst = lst->next;
		}
		lst = lst->next;
	}
	return (env_lst);
}
