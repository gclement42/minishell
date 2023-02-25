/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaisne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 16:21:07 by jlaisne           #+#    #+#             */
/*   Updated: 2023/02/25 09:53:31 by jlaisne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void 	print_export_list(t_env **list)
{
	t_env	*temp;

	sort_export(list);
	temp = *list;
	if (temp == NULL)
		return ;
	printf("declare -x %s=\"%s\"\n", temp->key, temp->content);
	while (temp->next != NULL)
	{
		temp = temp->next;
		if (ft_strncmp(temp->key, "_", 2) == 0)
		{
			if (temp->next)
				temp = temp->next;
		}
		else if (ft_strncmp(temp->content, "''", 3) != 0)
			printf("declare -x %s=\"%s\"\n", temp->key, temp->content);
		else
			printf("declare -x %s\n", temp->key);
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

static void	add_export(t_minish *var, char *env_var)
{
	char	**key_var;
	
	key_var = ft_split(env_var, '=');
	if (!key_var)
		exit(1); //FREE
	if (!key_var[1])
	{
	 	key_var[1] = ft_strdup("''");
		if (!key_var[1])
			exit(1); //FREE
		add_var_env(&var->exp_list, key_var[0], key_var[1]);
	}
	else
	{
		add_var_env(&var->env_list, key_var[0], key_var[1]);
		add_var_env(&var->exp_list, key_var[0], key_var[1]);
	}
}

void	export_env(t_minish *var)
{
	int		i;
	int		arg;
	char	**export_tab;

	i = 1;
	arg = wordcount(var->cmd, ' ');
	export_tab = ft_split(var->cmd, ' ');
	if (!export_tab)
		exit(1); //FREE
	if (arg != 1)
	{
		while (arg > 1)
		{
			add_export(var, export_tab[i]);
			arg--;
			i++;
		}
	}
	else
		print_export_list(&(var->exp_list));
	
}
