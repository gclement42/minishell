/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   typedef.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaisne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 10:14:44 by jlaisne           #+#    #+#             */
/*   Updated: 2023/05/04 12:41:52 by jlaisne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPEDEF_H
# define TYPEDEF_H

typedef enum s_marks
{
	SPACES,
	QUOTE,
	DQUOTE
}	t_marks;

typedef enum s_type
{
	CMD,
	OPT,
	ARG,
	PIPE,
	FILES,
	REDIRECT,
	S_SPACES
}	t_type;

typedef struct s_env
{
	char			*key;
	char			*content;
	struct s_env	*next;
}	t_env;

typedef struct s_pipex
{
	char	**env_cmd;
	int		*pipefds;
	char	**cmd;
	int		numpipes;
	int		fdin;
	int		fdout;
	int		status;
}	t_pipex;

typedef struct s_cmd
{
	char			*content;
	t_marks			marks;
	t_type			type;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_minish
{
	char			**env_tab;
	const char		**builtins;
	char			**arg_exec;
	t_env			*env_list;
	t_env			*exp_list;
	t_pipex			*pipex;
	char			*path;
	char			*cd_path;
	char			*cmd_line;
	char			*cmd;
	char			*pwd;
	char			*dir;
	char			*oldpwd;
	int				stdout_copy;
	int				lvl;
	int				status_parent;
	int				hdoc;
	unsigned char	return_status;
	t_cmd			*cmd_lst;
}	t_minish;

#endif