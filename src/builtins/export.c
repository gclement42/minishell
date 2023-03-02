/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gclement <gclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 16:21:07 by jlaisne           #+#    #+#             */
/*   Updated: 2023/03/01 10:29:23 by gclement         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	print_export_list(t_env **list)
{
	t_env	*temp;

	sort_export(list);
	temp = *list;
	if (temp == NULL)
		return ;
	while (temp != NULL)
	{
		if (ft_strncmp(temp->key, "_", 2) == 0)
		{
			if (temp->next)
				temp = temp->next;
		}
		if (ft_strncmp(temp->content, "''", 3) != 0)
			printf("declare -x %s=\"%s\"\n", temp->key, temp->content);
		else
			printf("declare -x %s\n", temp->key);
		temp = temp->next;
	}
}

void	sort_export(t_env **list)
{
	t_env	*temp;
	char	*holder_c;
	char	*holder_k;

	temp = *list;
	while (temp->next)
	{
		if (ft_strncmp(temp->key, temp->next->key, 20000) > 0)
		{
			holder_c = temp->content;
			holder_k = temp->key;
			temp->content = temp->next->content;
			temp->key = temp->next->key;
			temp->next->content = holder_c;
			temp->next->key = holder_k;
			temp = *list;
		}
		else
			temp = temp->next;
	}
}

static void	replace_content(t_minish *var, t_env *new_var)
{
	if (!new_var->content)
	{
		new_var->content = ft_strdup("''");
		if (!new_var->content)
			exit(1); //FREE
		modify_var(&var->exp_list, new_var->key, new_var->content);
	}
	else
	{
		modify_var(&var->exp_list, new_var->key, new_var->content);
		modify_var(&var->env_list, new_var->key, new_var->content);
	}	
}

static void	add_export(t_minish *var, t_env *new_var)
{
	while (new_var)
	{
		if (check_key(&var->exp_list, new_var->key) == 1)
		{
			if (!new_var->content)
			{
				new_var->content = ft_strdup("''");
				if (!new_var->content)
					exit(1); //FREE
				add_var_env(&var->exp_list, new_var->key, new_var->content);
			}
			else
			{
				add_var_env(&var->env_list, new_var->key, new_var->content);
				add_var_env(&var->exp_list, new_var->key, new_var->content);
			}
		}
		else
			replace_content(var, new_var);
		new_var = new_var->next;
	}
}

void	export_env(t_minish *var, t_env *new_var, int argc)
{
	if (argc != 0)
		add_export(var, new_var);
	else
		print_export_list(&(var->exp_list));
}
