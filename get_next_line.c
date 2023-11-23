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
			while (i < BUFFER_SIZE)
			{
				buffer[i] = '\0';
				i++;
			}
		
			printf("\nBuffer for the next string is: %s\n", buffer);
			return (str);
		}
		else
		{
			str = ft_strjoin(str, buffer);
			printf("\nString from remaining buffer is now: %s\n", str);
			i = 0;
			while (i < BUFFER_SIZE)
			{
				buffer[i] = '\0';
				i++;
			}
		}
	}
	i = 0;
	while (i < BUFFER_SIZE && buffer[i] != EOF)
			{
				buffer[i] = '\0';
				i++;
				//printf("\nbuffer is now: %s\n", buffer);
			}

	bytes_read = 1;
	
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		int j = bytes_read;
		while (j < BUFFER_SIZE)
			{
				buffer[j] = '\0';
				j++;
				//printf("\nbuffer is now: %s\n", buffer);
			}
		printf("\nBuffer after initial read: %s\n", buffer);
		if ((ptr = ft_strchr(buffer, '\n')) != NULL)
			printf("\n Newline found \n");

		if (ptr)
		{
			*ptr = '\0';
			str = ft_strjoin(str, buffer);
			printf("\nString after finding newline not in buffer is now: %s\n", str);
			ptr++;
			
			i = 0;
			while (*ptr && (i < bytes_read))
			{
				buffer[i] = *ptr;
				i++;
				ptr++;
			}
			printf("\nRemaining buffer for the next call is now: %s\n", buffer);
			printf("\nBytes_read is now: %d\n", bytes_read);
			while (i < BUFFER_SIZE)
			{
				buffer[i] = '\0';
				i++;
				//printf("\nbuffer is now: %s\n", buffer);
			}
			printf("\nAfter zeroing, remaining buffer for the next call is now: %s\n", buffer);
			printf("\nstring is now: %s\n", str);
			return(str) ;
		}
		else
		{
			str = ft_strjoin(str, buffer);
			printf("\n Str now is : %s\n", str);
		}
	}
	
	if (bytes_read <= 0 && str == NULL)
	{
		//free(buffer);
		return (NULL);
	}
	
	return (str);	
}


int	main (void)
{
	char	*str;
	int		fd;
	int i = 0;

	//str = calloc(1, 1);
	str = "test";
	fd = open("test.txt", O_RDONLY);
	if (fd == -1)
		return (-1);
	while (str[0] != '\0')
	{
		str = get_next_line(fd);
		printf("\nString[%d] is done: %s\n", i, str);
		i++;
	}
	free(str);
	close (fd);
	return (0);
}
