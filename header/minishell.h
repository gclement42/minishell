/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gclement <gclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 09:22:09 by jlaisne           #+#    #+#             */
/*   Updated: 2023/02/23 14:19:20 by gclement         ###   ########.fr       */
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

typedef enum s_marks {SPACES, QUOTE, DQUOTE}	t_marks;
typedef enum s_type {CMD, OPT, ARG, PIPE, FILES, REDIRECT}	t_type;

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
	t_env	**exp_list;
	char	*path;
	char	*cd_path;
	char	*cmd_line;
	char	*cmd;
  const char	**builtins;
  char		**arg_exec;
	char	*pwd;
	char	*dir;
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

int		cd(t_minish *var);

void	set_env(t_minish *var, char **envp, t_env **env, t_env **exp);
void	get_env(t_minish *var);
char	**split_env_var(char *env_line);

void	print_echo(int option, char *echo_line);

void	get_pwd(t_minish *var);

void	export_env(t_minish *var, int arg);

void	unset_env(t_minish *var);

char	*get_cwd(void);
void	add_var_env(t_env **lst, char *key, char *content);
int		check_key(t_env **lst, char *key);
char		*ft_strnstr_path(char *haystack, char *needle, size_t len);

/* ---- Utils list---- */
void		ft_lstadd_back_env(t_env **lst, t_env *new);
void		free_list(t_env *lst);

/* ---- Parsing ---- */
char		**parsing(char *cmd, t_minish env);
const char	**init_bultins_arr(void);
int			check_is_builtins(t_cmd *node, t_minish env);
char		**set_argxec(char **cmd);
size_t		count_len(char *cmd, char c);

/* ---- Parsing list Utils ---- */
void		*new_node_cmd\
(char	*word, t_marks marks, t_type type, t_cmd **lst);
t_cmd		*cmd_lst_last(t_cmd **lst);
void		lst_cmd_add_back(t_cmd **lst, t_cmd *new);
t_marks		get_marks(char c);
char		*prompt_for_quote_termination(char *cmd, char c);
t_cmd		*get_node(t_cmd *lst, t_type type);

/* ---- cut_cmd ---- */
void		get_opt(char *cmd, int *i, t_cmd **lst);
void		get_frst_word(char *cmd, int *i, t_cmd **lst);
void		get_word(char *cmd, int *i, size_t *start, t_cmd **lst);
void		get_redirect(char *cmd, int *i, t_cmd **lst, size_t *start);
void		get_file(char *cmd, int *i, t_cmd **lst);

/* ---- Builtins parsing ---- */
void		builtins_parsing(t_cmd *lst, int argc);
void		exit_parsing(char **arg);

/* ---- Memory Management ----*/
void		*free_2d_array(char **ptr);
void		free_and_exit(char *msg, char **arg);

void	get_cmd_line(t_minish *var, t_env **lst);
void	builtin_cmp(t_minish *var);
void	init_struct(t_minish *var, char **envp);

#endif