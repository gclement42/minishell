/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaisne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 16:44:59 by jlaisne           #+#    #+#             */
/*   Updated: 2023/02/24 16:51:30 by jlaisne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include </usr/include/readline/readline.h>
# include </usr/include/readline/history.h>
# include <errno.h>
# include <sys/types.h>
# include <dirent.h>
# include <signal.h>
# include <sys/ioctl.h>

typedef enum s_marks {SPACES, QUOTE, DQUOTE}	t_marks;
typedef enum s_type {CMD, OPT, ARG, PIPE, FILES, REDIRECT}	t_type;

typedef struct s_env
{
	char			*key;
	char			*content;
	struct s_env	*next;
}	t_env;

typedef struct s_minish
{
	char		**env_tab;
	const char	**builtins;
	char		**arg_exec;
	t_env		*env_list;
	t_env		*exp_list;
	char		*path;
	char		*cd_path;
	char		*cmd_line;
	char		*cmd;
	char		*pwd;
	char		*dir;
	char		*oldpwd;
	int			lvl;
}	t_minish;

typedef struct s_cmd
{
	char			*content;
	t_marks			marks;
	t_type			type;
	struct s_cmd	*next;
}	t_cmd;

/* ---- Utils ---- */
char	*ft_strnstr_path(char *haystack, char *needle, size_t len);
void	*free_array(char **ptr);
int		count_fist_word(char *env);

/* ---- Utils list---- */
void	ft_lstadd_back_env(t_env **lst, t_env *new);
t_env	*ft_lstnew_env(char *key, char *content);
void 	print_list(t_env **list);
void	free_list(t_env *lst);
int		ft_lstlen(t_env *lst);

void    exit_env(t_minish *var);

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

char	*ft_strnstr_path(char *haystack, char *needle, size_t len);
int		wordcount(char const *str, char c);

/* ---- Utils list---- */
void	ft_lstadd_back_env(t_env **lst, t_env *new);
t_env	*ft_lstnew_env(char *key, char *content);
void	free_list(t_env *lst);

void	get_cmd_line(t_minish *var, t_env **lst);
void	builtin_cmp(t_minish *var);
void	init_struct(t_minish *var, char **envp);

#endif