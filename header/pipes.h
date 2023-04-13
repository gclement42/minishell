/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gclement <gclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 17:07:35 by jlaisne           #+#    #+#             */
/*   Updated: 2023/04/13 10:04:37 by gclement         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPES_H
# define PIPES_H

# include "minishell.h"

void	pipex(t_minish *env, t_cmd *lst);

/* ----- Utils -----*/
void	join_slash(t_minish *env, char **path);
t_cmd	*lst_next(t_cmd *lst);
void	wait_id(t_pipex *var);
void	close_pipes(t_pipex *var);
void	close_all(void);

/* ----- Open ----- */
int		open_fd_in(t_minish *env, char *filename, t_cmd *lst);
int		open_fd_out(t_minish *env, char *filename, int redirect);
int		search_if_redirect(t_pipex *var, t_cmd *lst, t_minish *env);
int		create_heredoc(t_cmd *lst, t_pipex *var, t_minish *env);

/* ----- Error / Free / Close ---- */
void	free_close(t_pipex *var);
void	display_error(t_minish *env, char **tab, char *msg);
void	display_error_cmd(t_minish *env, char **tab, char *msg, char *cmd);
void	display_error_dir(t_minish *env, char **tab, char *msg, char *cmd);
void	close_pipes(t_pipex *var);

/* ----- Exec functions ----- */
void	exec_command(t_minish *env, char **path, char **cmd, char *envp[]);
char	**get_path(t_minish *env, char **envp);
/* ----- Dup ----- */

void	duplicate_fd(int fd, t_pipex *var, t_cmd *lst);

#endif
