/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gclement <gclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 14:05:38 by gclement          #+#    #+#             */
/*   Updated: 2023/05/04 15:26:36 by gclement         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "minishell.h"
# include "typedef.h"

void		builtins_router(t_cmd *cmd_node, int argc, t_minish *var);
void		display_lst(t_cmd *lst);
/* cut cmd*/
void		get_opt(char *cmd, int *i, t_cmd **lst);
int			get_frst_word(char *cmd, int *i, t_cmd **lst, t_minish *env);
void		*get_word(char *cmd, int *i, size_t *start, t_cmd **lst);
void		*get_redirect(char *cmd, int *i, t_cmd **lst, size_t *start);
void		*get_file(char *cmd, int *i, t_cmd **lst);
void		get_word_with_space(char *word, t_cmd **lst, int is_eol);
char		*remove_quote(char *str);
void		check_is_opt_or_arg(char *word, char marks, t_cmd **lst);
void		parse_router(char *cmd, int *i, size_t *start, t_cmd **lst);

/* parse cmd */
char		*replace_variable(char *str, t_minish *env, int *i);
char		**create_arr_exec(t_cmd *cmd);
int			is_here_doc(t_cmd *lst);
char		*check_if_replace_var_in_str(char *str, char del, t_minish *env);
void		browse_lst(t_cmd *lst, t_minish *env);

/* cmd list utils */
void		*new_node_cmd(char	*word, t_marks marks, t_type type, t_cmd **lst);
t_cmd		*cmd_lst_last(t_cmd **lst);
void		lst_cmd_add_back(t_cmd **lst, t_cmd *new);
t_cmd		*get_node(t_cmd *lst, t_type type, t_type end);

/* utils */
int			check_is_builtins(t_cmd *node, t_minish *env);
size_t		count_len(char *cmd, char c);
t_marks		get_marks(char c);
char		*search_key(t_env *lst_env, char *key);
int			count_type_in_lst(t_cmd *lst, t_type type, t_type delimiter);
int			check_is_valid_identifier(char *str, char *cmd);
int			is_all_char(char *word, char c);
int			check_if_unexpected_token(t_cmd *node, t_minish *env);
void		msg_invalid_opt(char *str, char *cmd, int ret_v);
char		**ft_ms_split(char const *s, char c);
int			skip_quote(int i, char *str, char del);
int			is_special_char(char c);
void		msg_unexpected_token(char token);
int			first_check_cmd(char *cmd);
void		delete_tab(char *str);

int			parsing(char *cmd, t_minish *env);
const char	**init_bultins_arr(void);
char		*join_all_arg(t_cmd *lst, int bools);

/* Builtins parsing */
t_env		*export_variable_parsing(t_cmd *lst, char *cmd_name);
void		cd_parsing(t_cmd *lst, int argc, t_minish *var);
void		echo_parsing(t_cmd *lst, t_minish *var);
void		unset_parsing(t_minish *var, t_cmd *lst);
void		exit_parsing(t_cmd *lst, t_minish *var);
void		export_parsing(t_minish *var, int argc, t_env *env, t_cmd *lst);
void		pwd_parsing(t_cmd *lst, t_minish *var);
char		*exit_num_parsing(t_cmd *lst, t_minish *var);
void		parsing_env(t_minish *var, t_cmd *arg);
t_cmd		*prompt_for_pipe(t_minish *env, t_cmd *lst, char *cmd);
t_cmd		*create_lst_cmd(char *cmd, t_cmd *lst, t_minish *env);

#endif