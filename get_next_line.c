/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akovalev <akovalev@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 16:33:15 by akovalev          #+#    #+#             */
/*   Updated: 2023/11/17 18:31:29 by akovalev         ###   ########.fr       */
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
	static char	*buffer;
	char		*temp;
	char		*ptr;
	char		*str;
	int			bytes_read;

	if (buffer == NULL)
		buffer = calloc(BUFFER_SIZE, 1);
	//if (!buffer)
	//	buffer = ft_strdup("");
	if (fd < 0)
		return (NULL);
	temp = malloc(BUFFER_SIZE + 1);
	if (!temp)
	{
		free(buffer);
		return (NULL);
	}

	bytes_read = 1;
	str = ft_strdup("");
	if (buffer[0] != '\0')
	{
		printf("\nbuffer is now: %s\n", buffer);
		str = ft_strjoin(str, buffer);
		printf("\nstr is now: %s\n", str);
		free (buffer);
	}
	while (bytes_read > 0)
	{
		bytes_read = read(fd, temp, BUFFER_SIZE);
		printf("\ntemp is now: %s\n", temp);
		//temp[bytes_read] = '\0';
		if ((ptr = ft_strchr(temp, '\n')) != NULL)
			printf("/n found /n");

		if (ptr)
		{
			printf("\nbuffer is now: %s\n", buffer);
			buffer = ft_strjoin(buffer, temp);
			printf("\nbuffer is now: %s\n", buffer);
			*ptr = '\0';
			printf("\nssstemp is now: %s\n", temp);
			str = ft_strjoin(str, temp);
			printf("\nstr is now: %s\n", str);
			break ;
		}
		else
		{
			str = ft_strjoin(str, temp);
			printf("\n str now is : %s\n", str);
		}
	}

	if (temp != NULL)
		free (temp);

	if (bytes_read <= 0 && str[0] == '\0' && buffer != NULL)
	{
		free(buffer);
		return (NULL);
	}

	return (str);
}


// int	main (void)
// {
// 	char	*str;
// 	int		fd;

// 	str = calloc(1, 1);
// 	fd = open("test.txt", O_RDONLY);
// 	if (fd == -1)
// 		return (-1);
// 	while (str != NULL)
// 	{
// 		str = get_next_line(fd);
// 		//printf("file contents: %s\n", str);
// 	}
// 	free(str);
// 	close (fd);
// 	return (0);
// }
