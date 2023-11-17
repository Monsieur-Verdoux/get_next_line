/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akovalev <akovalev@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 16:33:15 by akovalev          #+#    #+#             */
/*   Updated: 2023/11/17 16:03:05 by akovalev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*temp;
	char		*ptr;
	char		*str;
	char 		*remainder;
	int			bytes_read;

	buffer = malloc(BUFFER_SIZE);
	if (!buffer || fd < 1)
		return (NULL);
	temp = malloc(BUFFER_SIZE + 1);
	if (!temp)
	{
		free(buffer);
		return (NULL);
	}
	bytes_read = read(fd, temp, BUFFER_SIZE);
	if (bytes_read <= 0)
	{
		free(buffer);
		free(temp);
		return (NULL);
	}
	temp[bytes_read] = '\0';
	ptr = ft_strchr(temp, '\n');
	if (ptr)
	{
		str = ft_substr(temp, 0, (ptr - temp));
		remainder = ft_strdup(ptr + 1);
		free(buffer);
		buffer = remainder;
	}
	else
	{
		str = ft_strdup(temp);
		free(buffer);
		buffer = NULL;
	}

	free (temp);
	return (str);
}


// int	main (void)
// {
// 	char	*str;
// 	int		fd;

// 	fd = open("test.txt", O_RDONLY);
// 	if (fd == -1)
// 		return (-1);
// 	while (str != NULL)
// 	{
// 		str = get_next_line(fd);
// 		printf("file contents: %s\n", str);
// 	}
// 	//temp = get_next_line(fd);
// 	//printf("file contents: %s\n", temp);
// 	free(str);
// 	close (fd);
// 	return (0);
// }
