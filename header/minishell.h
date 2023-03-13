/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaisne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 09:22:09 by jlaisne           #+#    #+#             */
/*   Updated: 2023/03/09 15:31:53 by jlaisne          ###   ########.fr       */
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

/* ---- Utils ---- */
char	*ft_strnstr_path(char *haystack, char *needle, size_t len);
void	*free_array(char **ptr);
int		count_fist_word(char *env);
int		wordcount(char const *str, char c);
void	exit_free(t_minish *var);
char	**lst_to_tab(t_env **lst);

/* ---- Utils list---- */
void	ft_lstadd_back_env(t_env **lst, t_env *new);
t_env	*ft_lstnew_env(char *key, char *content);
void	print_list(t_env **list);
void	free_list(t_env *lst);
int		ft_lstlen(t_env *lst);

void	signal_handler(int status);
void	init_sigaction(void);

void	get_cmd_line(t_minish *var, t_env **lst);
void	builtin_cmp(t_minish *var);
void	init_struct(t_minish *var, char **envp);

void	*free_2d_array(char **ptr);

#endif