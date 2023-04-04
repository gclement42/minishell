/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_management.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaisne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 17:55:16 by gclement          #+#    #+#             */
/*   Updated: 2023/04/03 17:16:00 by jlaisne          ###   ########.fr       */
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
	if (var->var)
		free(var->var);
	if (var)
		free(var);
	exit (return_status);
}

void	free_env_list(t_env *lst)
{
	t_env	*temp;
	
	printf("\nCOUNT\n");
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

	while (lst)
	{
		temp = lst->next;
  	  if (lst->content && lst->type != S_SPACES)
    free(lst->content);
		free(lst);
		lst = temp;
	}
	free(lst);
}