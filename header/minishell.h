/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaisne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 16:44:59 by jlaisne           #+#    #+#             */
/*   Updated: 2023/02/25 10:27:10 by jlaisne          ###   ########.fr       */
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
# include <sys/wait.h>
# include <dirent.h>
# include <signal.h>
# include <sys/ioctl.h>
# include <fcntl.h>
# include "exec.h"
# include "typedef.h"
# include "pipes.h"

/* ---- Utils ---- */
char	*ft_strnstr_path(char *haystack, char *needle, size_t len);
void	*free_array(char **ptr);
int		count_fist_word(char *env);
int		wordcount(char const *str, char c);

/* ---- Utils list---- */
void	ft_lstadd_back_env(t_env **lst, t_env *new);
t_env	*ft_lstnew_env(char *key, char *content);
void	print_list(t_env **list);
void	free_list(t_env *lst);
int		ft_lstlen(t_env *lst);

/* --- MAIN TEMPORAIRE --- */
void	get_cmd_line(t_minish *var, t_env **lst);
void	builtin_cmp(t_minish *var);
void	init_struct(t_minish *var, char **envp);

#endif