/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaisne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 15:28:52 by gclement          #+#    #+#             */
/*   Updated: 2023/04/20 09:58:44 by jlaisne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

char	*ft_strchr(const char	*string, int searchCh)
{
	int	i;

	i = 0;
	if (string == NULL || string[i] == '\0')
		return (NULL);
	while (string[i])
	{
		if (string[i] == (char)searchCh)
			return (&((char *)string)[i + 1]);
		i++;
	}
	if (string[i] == (char)searchCh)
		return (&((char *)string)[i]);
	return (0);
}

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	x;
	size_t	dest_l;
	size_t	src_l;

	if (dest == NULL && size == 0)
		return (0);
	dest_l = ft_strlen(dest);
	src_l = ft_strlen(src);
	x = 0;
	i = dest_l;
	if (size <= dest_l)
		return (src_l + size);
	if (size > 0)
	{
		while (src[x] && (x < size - dest_l - 1))
		{
			dest[i] = src[x];
			i++;
			x++;
		}
		dest[i] = '\0';
	}
	return (dest_l + src_l);
}

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (size != 0)
	{
		while (src[i] && i < size - 1)
		{
			if (i < size - 1)
				dest[i] = src[i];
			i++;
		}
		dest[i] = '\0';
		return (ft_strlen(src));
	}
	else
		return (ft_strlen(src));
}

char	*ft_strdup(const char *source)
{
	char	*ptr;
	int		i;
	size_t	len;

	i = 0;
	len = (size_t)ft_strlen(source);
	ptr = malloc((len + 1) * sizeof(char));
	if (!ptr)
		return (NULL);
	while (0 < len)
	{
		ptr[i] = source[i];
		len--;
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}
