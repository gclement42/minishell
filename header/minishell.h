/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gclement <gclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 09:22:09 by jlaisne           #+#    #+#             */
/*   Updated: 2023/02/14 09:48:20 by gclement         ###   ########.fr       */
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
int			count_nb_arg(char **arg);

/* ---- Memory Management ----*/
void		*free_2d_array(char **ptr);
void		free_and_exit(char *msg, char **arg);

#endif