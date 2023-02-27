/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaisne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 10:51:57 by gclement          #+#    #+#             */
/*   Updated: 2023/02/27 16:40:53 by jlaisne          ###   ########.fr       */
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
		modify_var(&var->env_list, "PWD", var->cd_path);
		modify_var(&var->env_list, "OLDPWD", old_pwd);
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
		modify_var(&var->env_list, "PWD", home_dir);
		modify_var(&var->env_list, "OLDPWD", old_pwd);
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
			modify_var(&var->env_list, "OLDPWD", var->oldpwd);
			modify_var(&var->exp_list, "OLDPWD", var->oldpwd);
			return (0);
		}
	}
	if (chdir("/nfs/homes/gclement") == -1)
	{
		if (chdir("/nfs/homes/jlaisne") != -1)
			update_pwd_home(var, "/nfs/homes/jlaisne");
		else
			exit(1);
	}
	else
		update_pwd_home(var, "/nfs/homes/gclement");
	return (0);
}

int	cd(t_minish	*var)
{
	char	**dir;

	var->oldpwd = ft_strdup(get_cwd());
	printf("%s\n", var->oldpwd);
	dir = ft_split(var->cmd, ' ');
	if (!dir || !var->oldpwd)
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
	}
	else
	{
		var->cd_path = getcwd(NULL, 0);
		if (var->cd_path == NULL)
		{
			if (errno == ERANGE)
				stderr;
			stderr;
		}
		update_pwd(var);
		free_array(dir);
	}
	free(var->oldpwd);
	return (1);
}
