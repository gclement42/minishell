/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_parsing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gclement <gclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 10:37:47 by gclement          #+#    #+#             */
/*   Updated: 2023/02/25 17:54:34 by gclement         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	t_env	*create_tmp_lst_env(char **split_arg)
{
	t_env	*env_lst;
	t_env	*new;
	char	**split_key_value;
	int		i;

	env_lst = NULL;
	i = 0;
	while (ft_strchr(split_arg[i], '=') != 0)
	{
		if (split_arg[i][0] == '=')
			new = ft_lstnew_env(NULL, &split_arg[i][1]);
		else
		{
			split_key_value = split_env_var(split_arg[i]);
			if (!split_key_value)
				return (NULL);
			new = ft_lstnew_env(split_key_value[0], split_key_value[1]);
		}
		if (!new)
			exit (0);
		ft_lstadd_back_env(&env_lst, new);
		i++;
	}
	return (env_lst);
}

t_env	*export_variable_parsing(t_cmd *lst)
{
	t_env	*env_lst;
	char	**split_arg;

	env_lst = NULL;
	while (lst)
	{
		if (lst->type == OPT)
		{
			ft_putstr_fd("env : invalid option --", 2);
			ft_putstr_fd(lst->content, 2);
		}
		if (lst->type == ARG && ft_strchr(lst->content, '=') != 0)
		{
			split_arg = ft_split(lst->content, ' ');
			if (!split_arg)
				exit (0);
			env_lst = create_tmp_lst_env(split_arg);
			if (!env_lst)
				exit (0);
		}
		lst = lst->next;
	}
	return (env_lst);
}

char	*join_all_arg(t_cmd *lst)
{
	char	*arg_join;
	char	*tmp;

	lst = get_node(lst, ARG);
	tmp = lst->content;
	lst = lst->next;
	arg_join = tmp;
	while (lst && lst->type == ARG)
	{
		arg_join = ft_strjoin(tmp, lst->content);
		if (!arg_join)
			return (NULL);
		free (tmp);
		tmp = arg_join;
		lst = lst->next;
	}
	return (arg_join);
}

static	void	echo_parsing(t_cmd *lst)
{
	int		i;
	char	*arg_join;
	int		opt;

	i = 1;
	lst = lst->next;
	opt = 0;
	if (lst->type == OPT)
	{
		opt = 1;
		while (lst->content[i] == 'n')
			i++;
		if (lst->content[i])
		{
			lst->type = ARG;
			opt = 0;
		}
	}
	arg_join = join_all_arg(lst);
	if (!arg_join)
		exit (0);
	if (opt == OPT)
		print_echo(1, arg_join);
	else
		print_echo(0, arg_join);
}

// t_env *check_export_arg(t_env *lst)
// [
// 	t_env before;
// 	while (lst)
// 	{
// 		if (!lst->key)
// 		{
// 			l
// 		}
// 			lst = lst->next;
// 	}
// ]

void	builtins_parsing(t_cmd *lst, int argc, t_minish *var)
{
	t_cmd	*cmd_node;
	t_cmd	*arg_node;
	t_env	*env_lst;

	(void) env_lst;
	cmd_node = get_node(lst, CMD);
	arg_node = get_node(lst, ARG);
	if (ft_memcmp(cmd_node->content, "cd", 2) == 0)
	{
		if (argc > 1 || ft_strchr(arg_node->content, ' ') != 0)
			return (ft_putstr_fd("minishell: cd : too many arguments\n", 2));
		else if (argc == 0)
			cd(var, NULL);
		else
			cd(var, arg_node->content);
	}
	if (ft_memcmp(cmd_node->content, "pwd", 3) == 0)
		get_pwd(var);
	if (ft_memcmp(cmd_node->content, "env", 3) == 0)
		env_lst = export_variable_parsing(lst);
	// if (ft_memcmp(cmd_node, "unset", 5) == 0)
	// 	unset_parsing(arg);
	if (ft_memcmp(cmd_node, "export", 6) == 0)
	{
		env_lst = export_variable_parsing(lst);
	}
	// if (ft_memcmp(cmd_node, "exit", 4) == 0)
	// 	exit_parsing(arg);
	if (ft_memcmp(cmd_node->content, "echo", 4) == 0)
		echo_parsing(cmd_node);
}

// void	exit_parsing(char **arg)
// {
// 	printf("%d", ft_atoi(arg[1]));
// }
