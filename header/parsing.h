/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaisne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 14:05:38 by gclement          #+#    #+#             */
/*   Updated: 2023/03/17 14:57:46 by jlaisne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	PARSING_H
# define PARSING_H

# include "minishell.h"
# include "typedef.h"

void		builtins_router(t_cmd *lst, int argc, t_minish *var);

/* cut cmd*/
void		get_opt(char *cmd, int *i, t_cmd **lst);
void		get_frst_word(char *cmd, int *i, t_cmd **lst);
void		*get_word(char *cmd, int *i, size_t *start, t_cmd **lst);
void		get_redirect(char *cmd, int *i, t_cmd **lst, size_t *start);
void		get_file(char *cmd, int *i, t_cmd **lst);
void		get_word_with_space(char *word, t_cmd **lst, int is_eol);

/* parse cmd */
t_cmd		*replace_variable(t_cmd *lst, t_minish *env);
char		*prompt_for_quote_termination(char *cmd, char c);
char	    **create_arr_exec(t_cmd *cmd);
void		search_if_redirect(t_pipex *var, t_cmd *lst, int pipe_fd[2]);
void		create_heredoc(t_cmd *lst, int pipe_fd[2]);

/* cmd list utils */
void		*new_node_cmd(char	*word, t_marks marks, t_type type, t_cmd **lst);
t_cmd		*cmd_lst_last(t_cmd **lst);
void		lst_cmd_add_back(t_cmd **lst, t_cmd *new);
t_cmd		*get_node(t_cmd *lst, t_type type);

/* utils */
int			check_is_builtins(t_cmd *node, t_minish *env);
size_t		count_len(char *cmd, char c);
t_marks		get_marks(char c);
char		*search_key(t_env *lst_env, char *key);
int			count_type_in_lst(t_cmd *lst, t_type type);
int			check_is_valid_identifier(char *str, char *cmd);
int			is_all_char(char *word, char c);
int			check_if_unexpected_token(t_cmd *node);


void		parsing(char *cmd, t_minish *env);
const char	**init_bultins_arr(void);
char		*join_all_arg(t_cmd *lst);

/* Builtins parsing */
t_env		*export_variable_parsing(t_cmd *lst, char *cmd_name);
void		cd_parsing(t_cmd *lst, int argc, t_minish *var);
void		echo_parsing(t_cmd *lst);
void		unset_parsing(t_minish *var, t_cmd *lst);
void		exit_parsing(t_cmd *lst);
void		export_parsing(t_minish *var, int argc, t_env *env, t_cmd *lst);

#endif





 
