/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaisne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 10:51:57 by gclement          #+#    #+#             */
/*   Updated: 2023/04/24 10:08:16 by jlaisne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static void	update_pwd(t_minish *var)
{
	if ((check_key(&var->exp_list, "PWD") == 0))
		modify_var(var, &var->exp_list, "PWD", var->cd_path);
	if ((check_key(&var->exp_list, "OLDPWD") == 0))
		modify_var(var, &var->exp_list, "OLDPWD", var->oldpwd);
	if ((check_key(&var->env_list, "PWD") == 0))
		modify_var(var, &var->exp_list, "PWD", var->cd_path);
	if ((check_key(&var->env_list, "OLDPWD") == 0))
		modify_var(var, &var->env_list, "OLDPWD", var->oldpwd);
}

static void	update_pwd_home(t_minish *var, char *home_dir)
{
	char	*dir;

	dir = ft_strdup(home_dir);
	if (!dir)
		exit_free(var);
	if ((check_key(&var->exp_list, "PWD") == 0))
		modify_var(var, &var->exp_list, "PWD", dir);
	if ((check_key(&var->exp_list, "OLDPWD") == 0))
		modify_var(var, &var->exp_list, "OLDPWD", var->oldpwd);
	if ((check_key(&var->env_list, "PWD") == 0))
		modify_var(var, &var->exp_list, "PWD", dir);
	if ((check_key(&var->env_list, "OLDPWD") == 0))
		modify_var(var, &var->env_list, "OLDPWD", var->oldpwd);
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
		{
			g_return_status = 1;
			return (-1);
		}
	}
	else
		update_pwd_home(var, "/nfs/homes/gclement");
	return (0);
}

void	cd(t_minish *var, char *path)
{
	if (var->oldpwd)
		free (var->oldpwd);
	var->oldpwd = get_cwd();
	if (!var->oldpwd)
		exit_free(var);
	if (!path)
		cd_home(var);
	if (!ft_memcmp(path, "-", ft_strlen(path)))
		path = search_key(var->env_list, "OLDPWD");
	if (chdir(path) == -1)
	{
		perror("cd");
		g_return_status = 1;
	}
	else
	{
		if (var->cd_path)
			free(var->cd_path);
		var->cd_path = get_cwd();
		if (var->cd_path == NULL)
			exit_free(var);
		update_pwd(var);
	}
}
