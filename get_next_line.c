/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akovalev <akovalev@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 16:33:15 by akovalev          #+#    #+#             */
/*   Updated: 2023/11/27 19:15:52 by akovalev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

// char	*ft_strjoin_free(char *s1, char *s2)
// {
// 	char	*result;

// 	if (!s1 || !s2)
// 		return (NULL);

// 	result = ft_strjoin(s1, s2);
// 	free(s1);
// 	free(s2);

// 	return (result);
// }

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1];
	char		*ptr;
	char		*str;
	char		*temp;
	int			bytes_read;
	int			i;
	int 		j;
	size_t		str_len;
	
	i = 0;

	if (fd < 0 || BUFFER_SIZE <= 0 || read (fd, buffer, 0) < 0)
	{
		ft_bzero(buffer, BUFFER_SIZE);
		return (NULL);
	}
	str = ft_strdup("");
	if (str == NULL)
	{
		
		return (NULL);
	}
	if (*buffer)
	{
		ptr = ft_strchr(buffer, '\n');
		if (ptr)
		{
			*ptr = '\0';
			temp = str;
			str = ft_strjoin(temp, buffer);
			if (str == NULL)
			{
				free (temp);
				return (NULL);
			}
			free (temp);
			temp = NULL;
			temp = str;
			str = ft_strjoin(str, "\n");
			if (str == NULL)
			{
				free (temp);
				return (NULL);
			}
			free (temp);
			temp = NULL;
			ft_strncpy(buffer, ptr + 1, BUFFER_SIZE);
			return (str);
		}
		else
		{
			temp = str;
			str = ft_strjoin(temp, buffer);
			if (str == NULL)
			{
				free (temp);
				return (NULL);
			}
			free (temp);
			temp = NULL;
			ft_bzero(buffer, BUFFER_SIZE);
		}
	}

	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
			ft_bzero(buffer, BUFFER_SIZE);
		j = bytes_read;
		while (j < BUFFER_SIZE)
		{
			buffer[j] = '\0';
			j++;
		}
		ptr = ft_strchr(buffer, '\n');

		if (ptr)
		{
			*ptr = '\0';
			temp = str;
			str = ft_strjoin(temp, buffer);
			if (str == NULL)
			{
				free (temp);
				return (NULL);
			}
			free (temp);
			temp = NULL;
			temp = str;
			str = ft_strjoin(str, "\n");
			if (str == NULL)
			{
				free (temp);
				return (NULL);
			}
			free (temp);
			temp = NULL;
			ft_strncpy(buffer, ptr + 1, BUFFER_SIZE);
			return (str);
		}
		else
		{
			temp = str;
			str = ft_strjoin(temp, buffer);
			if (str == NULL)
			{
				free (temp);
				return (NULL);
			}
			free (temp);
			temp = NULL;
			ft_bzero(buffer, BUFFER_SIZE);
		}
	}
	str_len = ft_strlen(str);

	if (str_len > 0 && str[str_len - 1] != '\n')
	{
		return (str);
	}
	else
	{
		free(str);
		return (NULL);
	}
}


// int	main (void)
// {
// 	char	*str;
// 	int		fd;
// 	int i = 0;

// 	fd = open("test2.txt", O_RDONLY);
// 	if (fd == -1)
// 		return (-1);
// 	while ((str = get_next_line(fd)) != NULL)
// 	{
// 		printf("\nString[%d] is done: %s\n", i, str);
// 		free(str);
// 		i++;
// 	}
	
// 	close (fd);
// 	return (0);
// }
