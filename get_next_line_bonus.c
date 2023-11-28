/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akovalev <akovalev@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 18:40:13 by akovalev          #+#    #+#             */
/*   Updated: 2023/11/28 18:53:37 by akovalev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static void	gnl_bzero(void *s, size_t n)
{
	unsigned char	*str;

	str = (unsigned char *)s;
	while (n--)
		*str++ = '\0';
}

static char	*handle_buffer(char *ptr, char *str, char *buffer, int check)
{
	char	*temp;

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
		ft_strncpy(buffer, ptr + 1, BUFFER_SIZE);
		return (str);
	}
	gnl_bzero(buffer, BUFFER_SIZE);
	return (str);
}

static int	read_from_fd(int fd, char *buffer)
{
	int		bytes_read;
	int		i;

	bytes_read = read(fd, buffer, BUFFER_SIZE);
	if (bytes_read == -1)
		gnl_bzero(buffer, BUFFER_SIZE);
	else
	{
		i = bytes_read;
		while (i < BUFFER_SIZE)
		{
			buffer[i] = '\0';
			i++;
		}
	}
	return (bytes_read);
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
		bytes_read = read_from_fd(fd, buffer);
	while (bytes_read > 0)
	{
		ptr = ft_strchr(buffer, '\n');
		if (ptr)
			return (handle_buffer(ptr, str, buffer, 1));
		else
			str = handle_buffer(ptr, str, buffer, 0);
		if (str == NULL)
			return (NULL);
		bytes_read = read_from_fd(fd, buffer);
	}
	return (str);
}

char	*get_next_line(int fd)
{
	static char	buffer[1024][BUFFER_SIZE + 1];
	char		*str;

	if (fd < 0 || fd > 1023 || BUFFER_SIZE <= 0 || read (fd, buffer[fd], 0) < 0)
	{
		gnl_bzero(buffer[fd], BUFFER_SIZE);
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
