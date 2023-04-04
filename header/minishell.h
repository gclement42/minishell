/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaisne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 09:22:09 by jlaisne           #+#    #+#             */
/*   Updated: 2023/04/04 09:54:25 by gclement         ###   ########.fr       */
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
# include "exec.h"
# include "typedef.h"
# include "pipes.h"
# include "parsing.h"

extern unsigned char	return_status;

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
t_env	    *duplicate_node(t_env* lst);
void		print_list(t_env **list);
void		free_env_list(t_env *lst);
void		free_cmd_list(t_cmd *lst);
int			ft_lstlen(t_env *lst);

/* ---- Signals ---- */
void		signal_handler_newl(int sig);
void		signal_here_doc(int sig);
void		new_signal_here_doc(int sig);
void		signal_fork(int sig);
void		signal_parsing(int sig);
void		init_sigaction(void (*signal_handler)(int));
int			termios_save(struct termios *termios_save);
int			termios_restore(const struct termios termios_save);
int			termios_disable_quit();

void		get_cmd_line(t_minish *var, t_env **lst);
void		builtin_cmp(t_minish *var);
void		init_struct(t_minish *var, char **envp);

void		*free_2d_array(char **ptr);

#endif