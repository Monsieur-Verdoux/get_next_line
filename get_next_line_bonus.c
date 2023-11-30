/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akovalev <akovalev@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 16:33:15 by akovalev          #+#    #+#             */
/*   Updated: 2023/11/30 17:26:14 by akovalev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*handle_buffer(char *ptr, char *str, char *buffer, int check)
{
	char	*temp;
	size_t	n;

	n = BUFFER_SIZE;
	if (check == 1)
		*ptr = '\0';
	temp = str;
	str = ft_strjoin(temp, buffer);
	free (temp);
	temp = NULL;
	if (str == NULL)
		return (NULL);
	if (check == 1)
	{
		temp = str;
		str = ft_strjoin(str, "\n");
		free (temp);
		temp = NULL;
		if (str == NULL)
			return (NULL);
		ft_strlcpy(buffer, ptr + 1, BUFFER_SIZE);
	}
	while (n-- && check != 1)
		*buffer++ = '\0';
	return (str);
}

static char	*read_lines(int fd, char *buffer)
{
	char	*ptr;
	char	*str;
	int		bytes_read;

	str = ft_strdup("");
	if (str == NULL)
		return (NULL);
	bytes_read = 1;
	if (!*buffer)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		buffer[bytes_read] = '\0';
	}
	while (bytes_read > 0)
	{
		ptr = ft_strchr(buffer, '\n');
		if (ptr)
			return (handle_buffer(ptr, str, buffer, 1));
		else
			str = handle_buffer(ptr, str, buffer, 0);
		if (str == NULL)
			return (NULL);
		bytes_read = read(fd, buffer, BUFFER_SIZE);
	}
	return (str);
}

char	*get_next_line(int fd)
{
	static char	buffer[1024][BUFFER_SIZE + 1];
	char		*str;
	char		*ptr;
	size_t		n;

	n = BUFFER_SIZE;
	ptr = buffer[fd];
	if (fd < 0 || fd > 1023 || BUFFER_SIZE <= 0)
		return (NULL);
	if (read (fd, buffer[fd], 0) < 0)
	{
		while (n--)
			*ptr++ = '\0';
		return (NULL);
	}
	str = read_lines(fd, buffer[fd]);
	if (str == NULL)
		return (NULL);
	if (str[0] != '\0')
		return (str);
	else
	{
		free(str);
		return (NULL);
	}
}
