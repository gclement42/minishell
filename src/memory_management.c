/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_management.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gclement <gclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 17:55:16 by gclement          #+#    #+#             */
/*   Updated: 2023/04/04 10:24:27 by gclement         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*free_2d_array(char **ptr)
{
	int	i;

	i = 0;
	while (ptr[i])
	{
		free(ptr[i]);
		i++;
	}
	free(ptr);
	return (NULL);
}

void	free_and_exit(char *msg, char **arg)
{
	ft_putstr_fd(msg, 2);
	if (arg)
		free_2d_array(arg);
	exit (EXIT_SUCCESS);
}

void	exit_free(t_minish *var)
{
	if (var->env_list)
		free_env_list(var->env_list);
	if (var->exp_list)
		free_env_list(var->exp_list);
	if (var->oldpwd)
		free(var->oldpwd);
	if (var->builtins)
		free(var->builtins);
	if (var->cd_path)
		free(var->cd_path);
	if (var->var)
		free(var->var);
	if (var)
		free(var);
	exit (return_status);
}

void	free_env_list(t_env *lst)
{
	t_env	*temp;

	while (lst->next)
	{
		temp = lst->next;
		if (lst->key)
			free(lst->key);
		if (lst->content)
			free(lst->content);
		free(lst);
		lst = temp;
	}
	if (lst->key)
		free(lst->key);
	if (lst->content)
		free(lst->content);
	free(lst);
}

void	free_cmd_list(t_cmd *lst)
{
	t_cmd	*temp;

	ft_putstr_fd("\nFREE CMD LST\n", 2);
	while (lst)
	{
		temp = lst->next;
		if (lst->content)
    		free(lst->content);
		free(lst);
		lst = temp;
	}
	free(lst);
}
