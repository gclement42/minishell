/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaisne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 10:51:57 by gclement          #+#    #+#             */
/*   Updated: 2023/03/31 13:36:00 by jlaisne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static void	update_pwd(t_minish *var)
{
	t_env	*temp;
	char	*old_pwd;

	temp = var->env_list;
	if ((check_key(&temp, "PWD") == 0) && (check_key(&temp, "OLDPWD") == 0))
	{
		old_pwd = NULL;
		while (temp)
		{
			if (ft_strnstr(temp->key, "PWD", 4))
			{
				old_pwd = ft_strdup(temp->content);
				if (!old_pwd)
					exit(1); //FREE
			}
			temp = temp->next;
		}
		modify_var(var, &var->env_list, "PWD", var->cd_path);
		modify_var(var, &var->env_list, "OLDPWD", old_pwd);
	}
	if ((check_key(&var->exp_list, "PWD") == 0))
		add_var_env(&var->env_list, "PWD", var->cd_path);
	if ((check_key(&var->exp_list, "OLDPWD") == 0))
		add_var_env(&var->env_list, "OLDPWD", var->oldpwd);
}

static void	update_pwd_home(t_minish *var, char *home_dir)
{
	t_env	*temp;
	char	*old_pwd;

	temp = var->env_list;
	if ((check_key(&temp, "PWD") == 0) && (check_key(&temp, "OLDPWD") == 0))
	{
		old_pwd = NULL;
		while (temp)
		{
			if (ft_strnstr(temp->key, "PWD", 4))
			{
				old_pwd = ft_strdup(temp->content);
				if (!old_pwd)
					exit(1); //FREE
			}
			temp = temp->next;
		}
		modify_var(var, &var->env_list, "PWD", home_dir);
		modify_var(var, &var->env_list, "OLDPWD", old_pwd);
	}
	if ((check_key(&var->exp_list, "PWD") == 0))
		add_var_env(&var->env_list, "PWD", var->cd_path);
	if ((check_key(&var->exp_list, "OLDPWD") == 0))
		add_var_env(&var->env_list, "OLDPWD", var->oldpwd);
}

static int	cd_home(t_minish *var)
{
	if (ft_strncmp(var->oldpwd, "/nfs/homes/gclement", 20) == 0 \
		|| ft_strncmp(var->oldpwd, "/nfs/homes/jlaisne", 20) == 0)
	{
		if (check_key(&var->env_list, "OLDPWD") == 0)
		{
			modify_var(var, &var->env_list, "OLDPWD", var->oldpwd);
			modify_var(var, &var->exp_list, "OLDPWD", var->oldpwd);
			return (0);
		}
	}
	if (chdir("/nfs/homes/gclement") == -1)
	{
		if (chdir("/nfs/homes/jlaisne") != -1)
			update_pwd_home(var, "/nfs/homes/jlaisne");
		else
			return (-1);
	}
	else
		update_pwd_home(var, "/nfs/homes/gclement");
	return (0);
}

int	cd(t_minish *var, char *path)
{
	var->oldpwd = ft_strdup(get_cwd());
	if (!var->oldpwd)
		exit (1); // FREE
	if (!path)
		return (cd_home(var));
	if (chdir(path) == -1)
	{
		printf("cd: no such file or directory: %s\n", path);
		return (-1);
	}
	else
	{
		var->cd_path = get_cwd();
		if (var->cd_path == NULL)
			exit (1); // FREE
		update_pwd(var);
		free(var->oldpwd);
		return (0);
	}
}
