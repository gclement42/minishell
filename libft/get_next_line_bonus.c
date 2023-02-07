/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gclement <gclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 15:28:29 by gclement          #+#    #+#             */
/*   Updated: 2022/12/06 13:06:13 by gclement         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*dest;
	size_t	len_s1;
	size_t	len_s2;

	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	if (!(s1 == NULL || s2 == NULL))
	{	
		dest = malloc((len_s1 + len_s2 + 1) * sizeof(char));
		if (!dest)
			return (NULL);
		ft_strlcpy(dest, ((char *)s1), (len_s1 + 1));
		ft_strlcat(dest, s2, (len_s1 + (len_s2 + 1)));
		return (dest);
	}
	return (NULL);
}

char	*copy_line(char *str, int *bytes)
{
	char	*dest;
	int		i;

	i = 0;
	dest = NULL;
	if (str == NULL)
		return (NULL);
	if (ft_strchr(str, '\n') != 0 || *bytes != BUFFER_SIZE)
	{
		while (str[i] && str[i] != '\n')
			i++;
		if (str[i] == '\n')
			i++;
		dest = malloc((i + 1) * sizeof(char));
		if (!dest)
			return (NULL);
		ft_strlcpy(dest, str, (i + 1));
	}
	return (dest);
}

char	*read_and_join(char *dest, int fd, int *bytes)
{
	char	*str;
	char	*tmp;
	int		tmp_bytes;

	if (fd < 0)
		return (NULL);
	tmp_bytes = *bytes;
	str = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!str)
		return (NULL);
	if (*bytes != 0)
	{
		*bytes = read(fd, str, BUFFER_SIZE);
		if (*bytes == -1)
			return (NULL);
		str[*bytes] = '\0';
	}
	if (*bytes == 0 && tmp_bytes == -2)
		return (free (str), dest);
	if (dest != NULL && str != NULL)
	{
		tmp = ft_strjoin(dest, str);
		return (free(str), free(dest), tmp);
	}
	return (str);
}

char	*search_line(char *str, int fd, int *bytes)
{
	if (str == NULL || fd < 0)
		return (NULL);
	while ((*bytes == BUFFER_SIZE || *bytes == -2)
		&& ft_strchr(str, '\n') == 0)
	{
		str = read_and_join(str, fd, bytes);
		if (str == NULL)
			return (NULL);
	}
	return (str);
}

char	*get_next_line(int fd)
{
	static char	*overflow[256];
	char		*str;
	char		*tmp;
	int			bytes;

	bytes = -2;
	if (read(fd, NULL, 0) == -1)
		return (free(overflow[fd]), overflow[fd] = NULL, NULL);
	if (overflow[fd] != 0)
		str = search_line(overflow[fd], fd, &bytes);
	else
		str = read_and_join(NULL, fd, &bytes);
	if (str == NULL)
		return (NULL);
	str = search_line(str, fd, &bytes);
	if (str == NULL)
		return (NULL);
	tmp = copy_line(str, &bytes);
	if (ft_strchr(str, '\n') != 0 && str != NULL)
		overflow[fd] = ft_strdup(ft_strchr(str, '\n'));
	else
		overflow[fd] = NULL;
	if (tmp[0] == '\0' || tmp == NULL)
		return (free(str), free(tmp), free(overflow[fd]), NULL);
	return (free(str), tmp);
}
