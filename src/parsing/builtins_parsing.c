/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_parsing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gclement <gclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 10:37:47 by gclement          #+#    #+#             */
/*   Updated: 2023/03/13 11:13:44 by gclement         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_is_valid_identifier(char *str, char *cmd)
{
	int	i;

	i = 0;
	if (ft_isalnum(str[i]) == 0)
	{
		printf("minishell : %s : %s : not a valid identifier\n", \
			cmd, str);
		return (0);
	}
	i++;
	while (str[i])
	{
		if ((ft_isalpha(str[i]) == 0 && ft_isdigit(str[i]) == 0) && \
			str[i] != '$' && str[i] != '#' && str[i] != '=')
		{
			printf("minishell : %s : %s : not a valid identifier\n", \
			cmd, str);
			return (0);
		}
		i++;
	}
	return (1);
}

static	t_env	*create_tmp_lst_env(char *arg)
{
	t_env	*new;
	char	**split_key_value;
	int		i;

	i = 0;
	if (arg[0] == '=')
		new = ft_lstnew_env(NULL, &arg[1]);
	else
	{
		split_key_value = split_env_var(arg);
		if (!split_key_value)
			return (NULL);
		new = ft_lstnew_env(split_key_value[0], split_key_value[1]);
	}
	if (!new)
		return (NULL);
	i++;
	return (new);
}

t_env	*export_variable_parsing(t_cmd *lst, char *cmd_name)
{
	t_env	*env_lst;
	t_env	*new;

	env_lst = NULL;
	while (lst && lst->type != PIPE)
	{
		if (lst->type == OPT)
		{
			ft_putstr_fd("env : invalid option --", 2);
			ft_putstr_fd(lst->content, 2);
			return (NULL);
		}
		if (lst->type == ARG && ft_strchr(lst->content, '=') != 0)
		{
			new = create_tmp_lst_env(lst->content);
			if (!new)
				return (NULL);
			if (ft_strnstr(cmd_name, "export", 6) != 0 && new->key == NULL)
				free (new);
			else
				ft_lstadd_back_env(&env_lst, new);
		}
		lst = lst->next;
	}
	return (env_lst);
}

void	exit_parsing(t_minish *var, t_cmd *lst)
{
	int	i;

	i = 0;
	while (lst && lst->content[i])
	{
		if (!(lst->content[i] >= '0' && lst->content[i] <= '9'))
		{
			ft_putstr_fd("minishell: exit: ", 2);
			ft_putstr_fd(lst->content, 2);
			ft_putstr_fd(": numeric argument required\n", 2);
			break ;
		}
		i++;
	}
	exit_env(var);
}

void	create_heredoc(t_cmd *lst, int pipe_fd[2])
{
	char	*line;
	pid_t	pid;
	
	if (pipe(pipe_fd) < 0)
	{
		perror("pipe");
		exit (0);
	}
	pid = fork();
	if (pid < 0)
		return (perror("fork"), exit(0));
	if (pid == 0)
	{
		close(pipe_fd[0]);
		line = readline(">");
		while (ft_strncmp(lst->next->content, line, ft_strlen(line)) != 0)
		{
			if (write(pipe_fd[1], line, ft_strlen(line) + 1) < 0)
			{
				perror("write");
				//close(pipe_fd[0]);
				return ;
			}
			if (write(pipe_fd[1], "\n", 1) < 0)
				perror("write");
			free (line);
			line = readline(">");
		}
		exit (0);
	}
	wait (NULL);
	close(pipe_fd[1]);
	if(dup2(pipe_fd[0], STDIN_FILENO) < 0)
	{
		perror("dup2");
		exit(EXIT_FAILURE);
	}
}