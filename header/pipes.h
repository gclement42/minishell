/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaisne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 17:07:35 by jlaisne           #+#    #+#             */
/*   Updated: 2023/03/07 13:45:40 by jlaisne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPES_H
# define PIPES_H

# include "minishell.h"

void	pipex(t_minish *env, t_cmd *lst);

/* ----- Utils -----*/
void	join_slash(char **env);

/* ----- Open ----- */
void	open_fd_in(t_pipex *var, char *filename);
void	open_fd_out(t_pipex *var, char *filename, int redirect);

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

#endif
