/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gclement <gclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 15:05:17 by gclement          #+#    #+#             */
/*   Updated: 2023/03/03 10:41:16 by gclement         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	builtins_router(t_cmd *lst, int argc, t_minish *var)
{
	t_cmd	*cmd_node;
	t_cmd	*arg_node;
	t_env	*env_lst;
	size_t	cmd_len;

	cmd_node = get_node(lst, CMD);
	arg_node = get_node(lst, ARG);
	cmd_len = ft_strlen(cmd_node->content);
	env_lst = export_variable_parsing(lst, cmd_node->content);
	if (ft_memcmp(cmd_node->content, "cd", cmd_len) == 0)
		cd_parsing(arg_node, argc, var);
	if (ft_memcmp(cmd_node->content, "pwd", cmd_len) == 0)
		get_pwd(var);
	if (ft_memcmp(cmd_node->content, "env", cmd_len) == 0)
		get_env(var, &env_lst);
	if (ft_memcmp(cmd_node->content, "unset", cmd_len) == 0)
		unset_parsing(var, arg_node);
	if (ft_memcmp(cmd_node->content, "export", 6) == 0)
		export_env(var, env_lst, argc);
	if (ft_memcmp(cmd_node->content, "echo", 4) == 0)
		echo_parsing(cmd_node);
	if (ft_memcmp(cmd_node->content, "exit", 4) == 0)
		exit_parsing(var, arg_node);
}

char	**create_arr_exec(t_cmd *cmd)
{
	t_cmd	*tmp;
	char	**arr_exec;
	int		len;
	int		x;

	len = 0;
	x = 0;
	tmp = cmd;
	while (tmp)
	{
		if (tmp->type == PIPE)
			break;
		len++;
		tmp = tmp->next;
	}
	arr_exec = malloc((len + 1) * sizeof(char *));
	if (!arr_exec)
		return (NULL);
	while (x < len)
	{
		arr_exec[x] = cmd->content;
		cmd = cmd->next;
		x++;
	}
	arr_exec[x] = NULL;
	return (arr_exec);
}

static t_cmd	*parse_cmd(char *cmd, t_cmd **lst)
{
	int		i;
	size_t	start;
	char	*word;

	i = 0;
	get_redirect(cmd, &i, lst, &start);
	get_frst_word(cmd, &i, lst);
	get_opt(cmd, &i, lst);
	start = i;
	while (cmd[i])
	{
		if (cmd[i] == '\'' || cmd[i] == '"')
			get_word(cmd, &i, &start, lst);
		if (cmd[i] == '>' || cmd[i] == '<')
			get_redirect(cmd, &i, lst, &start);
		i++;
	}
	if (start < (size_t)i && cmd[start])
	{
		word = ft_substr(cmd, start, ft_strlen(cmd) - start);
		if (!word)
			return (NULL);
		get_word_with_space(word, lst);
	}
	return (*lst);
}

static	t_cmd *create_lst_cmd(char *cmd)
{
	char	**split_cmd;
	t_cmd	*lst;
	int		i;
	
	i = 0;
	lst = NULL;
	split_cmd = ft_split(cmd, '|');
	if (!split_cmd)
		exit (0);
	while (split_cmd[i])
	{
		lst = parse_cmd(split_cmd[i], &lst);
		i++;
		if (split_cmd[i])
			new_node_cmd("|", SPACES, PIPE, &lst);
	}
	return (lst);
}

void	search_if_heredoc(t_cmd *lst, int pipe_fd[2])
{
	char	*line;

	while (lst)
	{
		if (ft_memcmp("<<", lst->content, ft_strlen(lst->content)) == 0 
			&& lst->type == REDIRECT)
		{
			pipe(pipe_fd);
			//close(pipe_fd[1]);
			line = readline(">");
			while (ft_strncmp(lst->next->content, line, ft_strlen(line)) != 0)
			{
				line[ft_strlen(line)] = '\n';
				if (write(pipe_fd[1], line, ft_strlen(line) + 1) < 0)
				{
					perror("minishell");
					close(pipe_fd[0]);
					return ;
				}
				free (line);
				line = readline(">");
			}
			close(pipe_fd[1]);
		}
		lst = lst->next;
	}
	char buffer[1024];
	int	n;
	while ((n = read(pipe_fd[0], buffer, 1024)) > 0) 
	{
        printf("read %d bytes from the pipe: %s\n", n, buffer);
    }
}

void	parsing(char *cmd, t_minish *env)
{
	t_cmd	*lst;
	int		arg_count;
	char	**arr_exec;
	int 	pipe_fd[2];

	if (cmd[0] == '\0')
		return ;
	(void) arr_exec;
	lst = create_lst_cmd(cmd);
	replace_variable(lst, env);
	search_if_heredoc(lst, pipe_fd);
	arg_count = count_type_in_lst(lst, ARG);
	if (check_is_builtins(get_node(lst, CMD), env) == 1)
		builtins_router(lst, arg_count, env);
	// else
	// {
	// 	arr_exec = create_arr_exec(lst);
	// 	pipex(2, arr_exec, env->env_list);
	// }		
	return ;
}