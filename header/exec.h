/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaisne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 09:51:41 by jlaisne           #+#    #+#             */
/*   Updated: 2023/02/25 10:16:34 by jlaisne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "minishell.h"
# include "typedef.h"

void	exit_env(t_minish *var);

int		cd(t_minish *var);

void	set_env(char **envp, t_env **env, t_env **exp);
void	get_env(t_minish *var, t_env **add_env);
char	**split_env_var(char *env_line);

void	print_echo(int option, char *echo_line);

void	get_pwd(t_minish *var);

void	export_env(t_minish *var);
void	sort_export(t_env **list);

void	print_export_list(t_env **list);

void	unset_env(t_minish *var);

char	*get_cwd(void);
void	add_var_env(t_env **lst, char *key, char *content);
int		check_key(t_env **lst, char *key);
void	modify_var(t_env **list, char *key, char *str);

#endif