/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaisne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 09:22:09 by jlaisne           #+#    #+#             */
/*   Updated: 2023/02/16 11:01:22 by jlaisne          ###   ########.fr       */
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

typedef struct s_env
{
	char			*key;
	char			*content;
	struct s_env	*next;
} t_env;

typedef struct s_minish
{
	char	**env_tab;
	t_env	**env_list;
	char	**unset_tab;
	char	*path;
	char	*cd_path;
	char	*cmd_line;
	char	*cmd;
	char	*pwd;
	char	*dir;
	
}	t_minish;

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

int		cd(t_minish *var);

void	set_env(t_minish *var, t_env **env, char **envp);
void	get_env(t_minish *var);

void	print_echo(int option, char *echo_line);

void	get_pwd(t_minish *var);

void	export_env(t_minish *var, int arg);


char	*get_cwd(void);
static void	add_var_env(t_minish *var, char *key, char *content);

#endif