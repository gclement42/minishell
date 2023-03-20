/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaisne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 17:07:35 by jlaisne           #+#    #+#             */
/*   Updated: 2023/03/19 16:33:24 by jlaisne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPES_H
# define PIPES_H

# include "minishell.h"

void	pipex(t_minish *env, t_cmd *lst);

/* ----- Utils -----*/
void	join_slash(char **env);
t_cmd	*lst_next(t_cmd *lst);
void	wait_id(t_pipex *var);
void	close_pipes(t_pipex *var);

/* ----- Open ----- */
void	open_fd_in(t_pipex *var, char *filename, t_cmd *lst);
void	open_fd_out(t_pipex *var, char *filename, int redirect);
void	search_if_redirect(t_pipex *var, t_cmd *lst, int pipe_fd[2]);

/* ----- Error / Free / Close ---- */
void	free_close(t_pipex *var);
void	free_tab(char **tab);
void	display_error(char **tab, char *msg);
void	display_error_cmd(char **tab, char *msg, char *cmd);
void	close_pipes(t_pipex *var);

/* ----- Exec functions ----- */
char	**get_command(char *arg, char **env);
void	exec_command(t_pipex *var, char **env, char **cmd, char *envp[]);
char	**get_path(char *envp[]);
/* ----- Dup ----- */

void	duplicate_fd(int fd, t_pipex *var, t_cmd *lst);

#endif
