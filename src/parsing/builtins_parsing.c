/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_parsing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gclement <gclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 10:37:47 by gclement          #+#    #+#             */
/*   Updated: 2023/03/02 13:57:57 by gclement         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	t_env	*create_tmp_lst_env(char *arg)
{
	t_env	*new;
	char	**split_key_value;
	int		i;

	i = 0;
	if (arg[0] == '=')
		new = ft_lstnew_env(NULL, &arg[1]);
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
	while (lst)
	{
		if (lst->type == OPT)
		{
			ft_putstr_fd("env : invalid option --", 2);
			ft_putstr_fd(lst->content, 2);
		}
		if (lst->type == ARG && ft_strchr(lst->content, '=') != 0)
		{
			new = create_tmp_lst_env(lst->content);
			if (!new)
				return (NULL);
			if (ft_strnstr(cmd_name, "export", 6) != 0 && new->key == NULL)
				free (new);
			else
				ft_lstadd_back_env(&env_lst, new);
		}
		lst = lst->next;
	}
	return (env_lst);
}

void	unset_parsing(t_minish *var, t_cmd *lst)
{
	int		i;

	i = 0;
	while (lst)
	{
		while (lst->content[i])
		{
			if (ft_isalpha(lst->content[i]) == 0 && lst->content[i] != '$')
			{
				printf("minishell : unset : %s : not a valid identifier\n", \
				lst->content);
				break ;
			}
			i++;
		}
		remove_var_env(var, lst->content);
		lst = lst->next;
	}
}

void	exit_parsing(t_minish *var, t_cmd *lst)
{
	int	i;

	i = 0;
	while (lst->content[i])
	{
		if (!(lst->content[i] >= '0' && lst->content[i] <= '9'))
		{
			ft_putstr_fd("minishell: exit: ", 2);
			ft_putstr_fd(lst->content, 2);
			ft_putstr_fd(": numeric argument required\n", 2);
			break ;
		}
		i++;
	}
	exit_env(var);
}
