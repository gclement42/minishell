#include "minishell.h"

static char *join_content_next_var(char *content, char *var_content)
{
	char	*eow;
	char	*join_content;
	int		start;

	start = 0;
	while (content[start] != '$')
		start++;
	start++;
	while (ft_isalpha(content[start]) == 1 || content[start] == '?')
		start++;
	eow = ft_substr(content, start, (ft_strlen(content)) - start);
	if (!eow)
		return (NULL);
	join_content = ft_strjoin(var_content, eow);
	return (free(var_content), free(eow), join_content);	
}

static	char *join_new_content(char *new_content, char *content, int size)
{
	char	*str_begin;
	char	*str;
	
	if (size > 0)
	{
		str_begin = malloc((size + 1) * sizeof(char));
		if (!str_begin)
			return (NULL);
		str_begin = ft_memcpy(str_begin, content, size);
		str_begin[size] = '\0';
		str = ft_strjoin(str_begin, new_content);
		str = join_content_next_var(content, str);
		return (str);
	}
	else
	{
		free(content);
		if (new_content)
			content = new_content;
		else
			content = " ";
	}
	return (content);
}


t_cmd	*replace_variable(t_cmd *lst, t_minish *env)
{
	char	*new_content;
	int		i;

	while (lst)
	{
		i = -1;
		while (lst->content[++i])
		{
			if (lst->content[i] == '$' && lst->marks != QUOTE)
			{
				if (lst->content[i - 1] == '\\')
					new_content = ft_strdup(&lst->content[i]);
				else
					new_content = search_key(env->env_list, &lst->content[i + 1]);
				if (lst->content[i - 1] == '\\')
					lst->content = new_content;
				else if (new_content)
					lst->content = join_new_content(new_content, lst->content, i);
				if (!lst->content)
					return (NULL);
			}
		}
		lst = lst->next;
	}
	return (lst);
}