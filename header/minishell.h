/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaisne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 09:22:09 by jlaisne           #+#    #+#             */
/*   Updated: 2023/04/26 11:20:52 by jlaisne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <limits.h>
# include </usr/include/readline/readline.h>
# include </usr/include/readline/history.h>
# include <errno.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <dirent.h>
# include <sys/ioctl.h>
# include <fcntl.h>
# include <signal.h>
# include <termios.h>
# include "typedef.h"
# include "exec.h"
# include "pipes.h"
# include "parsing.h"

extern unsigned char	g_return_status;

/* ---- Utils ---- */
char		*ft_strnstr_path(char *haystack, char *needle, size_t len);
void		*free_array(char **ptr);
size_t		count_first_word(char *env, char c);
int			wordcount(char const *str, char c);
void		exit_free(t_minish *var);
char		**lst_to_tab(t_env **lst);
long long	ft_atoll(const char *str);
size_t		check_isspace(const char *str);

/* ---- Utils list---- */
void		ft_lstadd_back_env(t_env **lst, t_env *new);
t_env		*ft_lstnew_env(char *key, char *content);
t_env		*duplicate_node(t_env *lst);
void		free_env_list(t_env *lst);
void		free_cmd_list(t_cmd *lst);
int			ft_lstlen(t_env *lst);
t_env		*get_key_node(t_env *lst, char *key);

/* ---- Signals ---- */
int			signal_ignore(void);
void		signal_handler_newl(int sig);
void		new_signal_here_doc(int sig);
void		signal_fork(int sig);
void		signal_parsing(int sig);
int			init_sigaction(void (*signal_handler)(int));

void		get_cmd_line(t_minish *var, t_env **lst);
void		builtin_cmp(t_minish *var);

void		*free_2d_array(char **ptr);

#endif