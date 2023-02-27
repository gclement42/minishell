/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaisne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 14:05:38 by gclement          #+#    #+#             */
/*   Updated: 2023/02/25 14:17:03 by jlaisne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "minishell.h"
# include "typedef.h"

void    builtins_parsing(t_cmd *lst, int argc);
void    get_opt(char *cmd, int *i, t_cmd **lst);
void    get_frst_word(char *cmd, int *i, t_cmd **lst);
void    get_word(char *cmd, int *i, size_t *start, t_cmd **lst);
void    get_redirect(char *cmd, int *i, t_cmd **lst, size_t *start);
void    get_file(char *cmd, int *i, t_cmd **lst);
void    *new_node_cmd(char    *word, t_marks marks, t_type type, t_cmd **lst);
t_cmd    *cmd_lst_last(t_cmd **lst);
void    lst_cmd_add_back(t_cmd **lst, t_cmd *new);
t_cmd    *get_node(t_cmd *lst, t_type type);
char    **set_argxec(char **cmd);
int        check_is_builtins(t_cmd *node, t_minish env);
size_t    count_len(char *cmd, char c);
t_marks    get_marks(char c);
char    *prompt_for_quote_termination(char *cmd, char c);
char    **parsing(char *cmd, t_minish env);

#endif