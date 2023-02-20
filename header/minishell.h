/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gclement <gclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 09:22:09 by jlaisne           #+#    #+#             */
/*   Updated: 2023/02/20 10:18:21 by gclement         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include </usr/include/readline/readline.h>
# include </usr/include/readline/history.h>

# include <sys/types.h>
# include <dirent.h>
# include <signal.h>

typedef enum s_marks {SPACES, QUOTE, DQUOTE}	t_marks;
typedef enum s_type {CMD, OPT, ARG, PIPE, FILES, REDIRECT}	t_type;

typedef struct s_env
{
	char			*content;
	struct s_env	*next;
}	t_env;

typedef struct s_minish
{
	char		**env_tab;
	t_env		**env_list;
	char		**unset_tab;
	char		**arg_exec;
	const char	**builtins;
	char		*cmd;
	char		*pwd;
	char		*dir;
}	t_minish;

typedef struct s_cmd
{
	char			*content;
	t_marks			marks;
	t_type			type;
	struct s_cmd	*next;
}	t_cmd;

/* ---- Utils ---- */
char		*ft_strnstr_path(char *haystack, char *needle, size_t len);

/* ---- Utils list---- */
void		ft_lstadd_back_env(t_env **lst, t_env *new);
t_env		*ft_lstnew_env(char *content);
void		print_list(t_env *list);
void		free_list(t_env *lst);
int			cd(char *arg);

/* ---- Parsing ---- */
char		**parsing(char *cmd, t_minish env);
const char	**init_bultins_arr(void);
int			check_is_builtins(const char *cmd, t_minish env);
char		**set_argxec(char **cmd);
size_t		count_len(char *cmd, char c);

/* ---- Parsing list Utils ---- */
void		*new_node_cmd\
(char	*word, t_marks marks, t_type type, t_cmd **lst);
t_cmd		*cmd_lst_last(t_cmd **lst);
void		lst_cmd_add_back(t_cmd **lst, t_cmd *new);
t_marks		get_marks(char c);
char		*prompt_for_quote_termination(char *cmd, char c);

/* ---- cut_cmd ---- */
void		get_opt(char *cmd, int *i, t_cmd **lst);
void		get_frst_word(char *cmd, int *i, t_cmd **lst);
void		get_word(char *cmd, int *i, size_t *start, t_cmd **lst);
void		get_redirect(char *cmd, int *i, t_cmd **lst, size_t *start);
void		get_file(char *cmd, int *i, t_cmd **lst);

/* ---- Builtins parsing ---- */
void		builtins_parsing(char **arg, int argc);
void		exit_parsing(char **arg);

/* ---- Memory Management ----*/
void		*free_2d_array(char **ptr);
void		free_and_exit(char *msg, char **arg);

#endif