/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akovalev <akovalev@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 16:33:15 by akovalev          #+#    #+#             */
/*   Updated: 2023/11/20 19:03:56 by akovalev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*result;

	if (!s1 || !s2)
		return (NULL);

	result = ft_strjoin(s1, s2);
	free(s1);
	free(s2);

	return (result);
}

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE];
	char		*ptr;
	char		*str;
	int			bytes_read;
	int 		i;
	
	i = 0;

	if (fd < 0)
		return (NULL);
	str = ft_strdup("");

	if (*buffer)
	{
		ptr = ft_strchr(buffer, '\n');
		if (ptr)
		{
			*ptr = '\0';
			str = ft_strjoin(str, buffer);
			ptr++;
			while (*ptr)
			{
				buffer[i] = *ptr;
				i++;
				ptr++;
			}
			return (str);
		}
		else
			str = ft_strjoin(str, buffer);
	}

	bytes_read = 1;
	
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if ((ptr = ft_strchr(buffer, '\n')) != NULL)
			printf("/n found /n");

		if (ptr)
		{
			*ptr = '\0';
			str = ft_strjoin(str, buffer);
			ptr++;
			i = 0;
			while (*ptr)
			{
				buffer[i] = *ptr;
				i++;
				ptr++;
			}
			while (i < BUFFER_SIZE)
				buffer[i] = '\0';
			printf("\nstring is now: %s\n", str);
			break ;
		}
		else
		{
			str = ft_strjoin(str, buffer);
			printf("\n Str now is : %s\n", str);
		}
	}

	if (bytes_read <= 0 && str[0] == '\0' && *buffer)
	{
		free(buffer);
		return (NULL);
	}

	return (str);
}


int	main (void)
{
	char	*str;
	int		fd;

	str = calloc(1, 1);
	fd = open("test.txt", O_RDONLY);
	if (fd == -1)
		return (-1);
	while (str != NULL)
	{
		str = get_next_line(fd);
		//printf("file contents: %s\n", str);
	}
	free(str);
	close (fd);
	return (0);
}
