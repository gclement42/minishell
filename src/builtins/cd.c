/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaisne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 10:51:57 by gclement          #+#    #+#             */
/*   Updated: 2023/02/21 15:02:33 by jlaisne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	update_pwd(t_minish *var)
{
	t_env	*temp;
	t_env	*temp_s;
	char	*new_path;
	char	*old_pwd;

	temp = var->env_list;
	temp_s = temp;
	old_pwd = ft_strdup("OLD");
	new_path = ft_strdup(var->cd_path);
	if (!new_path || !old_pwd)
		exit(1); // FREE
	while (temp)
	{
		if (ft_strnstr(temp->key, "PWD", 3))
		{
			old_pwd = ft_strjoin(old_pwd, temp->content);
			temp->content = new_path;
		}
		if (ft_strnstr(temp->key, "OLDPWD", 6))
			temp->content = old_pwd;
		temp = temp->next;
	}
	temp = temp_s;
	var->env_list = temp;
}

static void	update_pwd_home(t_minish *var, char *home_dir)
{
	t_env	*temp;
	t_env	*temp_s;
	char	*old_pwd;

	temp = var->env_list;
	temp_s = temp;
	old_pwd = ft_strdup("OLD");
	if (!old_pwd)
		exit(1); // FREE
	while (temp)
	{
		if (ft_strnstr(temp->key, "PWD", 3))
		{
			old_pwd = ft_strjoin(old_pwd, temp->content);
			temp->content = ft_strdup(home_dir);
			if (!old_pwd || !temp->content)
				exit (1); //FREE
		}
		if (ft_strnstr(temp->key, "OLDPWD", 6))
			temp->content = old_pwd;
		temp = temp->next;
	}
	temp = temp_s;
	var->env_list = temp;	
}

static int	cd_home	(t_minish *var)
{
	char	*home_dir;
	t_env	*temp;
	
	temp = var->env_list;
	while (temp)
	{
		if (ft_strnstr(temp->key, "USER_ZDOTDIR", 12))
			break;
		temp = temp->next;
	}
	home_dir = ft_strdup(temp->content);
	if (!home_dir)
		exit(1); //FREE
	if (chdir(home_dir) == -1)
	 	return (-1);
	update_pwd_home(var, home_dir);
	return (0);
}

int	cd(t_minish	*var)
{
	char	**dir;

	dir = ft_split(var->cmd, ' ');
	if (!dir)
		return (-1);
	if (!dir[1])
	{
		cd_home(var);
		return (0);
	}
	if (chdir(dir[1]) == -1)
	{
		printf("cd: no such file or directory: %s\n", dir[1]);
		free_array(dir);
		return (-1);
	}
	else
	{
		if ((var->cd_path = getcwd(NULL, 0)) == NULL)
		{
			if (errno == ERANGE)
				stderr;
			stderr;
		}
		update_pwd(var);
		free_array(dir);
		return (1);
	}
}
