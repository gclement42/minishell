/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gclement <gclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 09:51:41 by jlaisne           #+#    #+#             */
/*   Updated: 2023/03/01 10:47:09 by gclement         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "minishell.h"
# include "typedef.h"

/* ---- exit ---- */
void	exit_env(t_minish *var);

/* ---- cd ---- */
int		cd(t_minish *var, char *path);

/* ---- env ---- */
void	set_env(char **envp, t_env **env, t_env **exp);
void	get_env(t_minish *var, t_env **add_env);
char	**split_env_var(char *env_line);

/* ---- echo ---- */
void	print_echo(int option, char *echo_line);

/* ---- pwd ---- */
void	get_pwd(t_minish *var);

/* ---- export ---- */
void	export_env(t_minish *var, t_env *new_var, int argc);
void	sort_export(t_env **list);
void	print_export_list(t_env **list);

/* ---- unset ---- */
void	unset_env(t_minish *var, t_env *unset_var);
void	remove_var_env(t_minish *var, char *unset_tab);

/* ---- builtins utils ---- */
char	*get_cwd(void);
void	add_var_env(t_env **lst, char *key, char *content);
int		check_key(t_env **lst, char *key);
void	modify_var(t_env **list, char *key, char *str);

#endif