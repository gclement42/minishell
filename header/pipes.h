/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaisne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 17:07:35 by jlaisne           #+#    #+#             */
/*   Updated: 2023/02/27 15:59:06 by jlaisne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPES_H
# define PIPES_H

# include "minishell.h"

typedef struct s_pipex
{
	char	**env_cmd;
	char	**arg;
	int		*id;
	int		file[2];
	int		fd1;
	int		fd2;
	int		status;
}	t_pipex;

int		pipex(int arg, char **argv, char **env);

/* ----- Utils -----*/
void	join_slash(char **env);
void	open_fd(t_pipex *var, char **argv);
char	**lst_to_tab(t_env **list);

/* ----- Error / Free / Close ---- */
void	free_close(t_pipex *var);
void	close_pipe(t_pipex *var);
void	free_tab(char **tab);
void	display_error(char **tab, char *msg);
void	display_error_cmd(char **tab, char *msg, char *cmd);

/* ----- Exec functions ----- */
char	**get_command(char *arg, char **env);
void	exec_command(t_pipex *var, char **env, char **cmd, char *envp[]);
char	**get_path(char *envp[]);

#endif
