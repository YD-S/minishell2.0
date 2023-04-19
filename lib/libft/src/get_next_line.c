/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysingh <ysingh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 20:03:17 by ysingh            #+#    #+#             */
/*   Updated: 2022/12/09 03:49:11 by ysingh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*gnl_buffer(char *buff)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	while (buff[i] && buff[i] != '\n')
		i++;
	if (!buff[i])
	{
		free(buff);
		return (NULL);
	}
	str = gnl_calloc((gnl_strlen(buff) - i + 1), sizeof(char));
	if (!str)
		return (NULL);
	i++;
	j = 0;
	while (buff[i])
		str[j++] = buff[i++];
	free(buff);
	return (str);
}

static char	*gnl_line(char *temp)
{
	int		j;
	char	*str;

	j = 0;
	if (!temp[j])
		return (NULL);
	while (temp[j] && temp[j] != '\n')
		j++;
	str = gnl_calloc((j + 2), sizeof(char));
	if (!str)
		return (NULL);
	j = 0;
	while (temp[j] && temp[j] != '\n')
	{
		str[j] = temp[j];
		j++;
	}
	if (temp[j] == '\n')
	{
		str[j] = temp[j];
		j++;
	}
	return (str);
}

static char	*gnl_read(int fd, char *buff)
{
	char	*temp;
	int		n;

	temp = gnl_calloc((BUFFER_SIZE + 2), sizeof(char));
	if (!temp)
		return (NULL);
	n = 1;
	while (!(gnl_strchr(buff, '\n')) && n != 0)
	{
		n = read(fd, temp, BUFFER_SIZE);
		if (n == -1)
		{
			if (buff != NULL)
				free(buff);
			return (free(temp), NULL);
		}
		temp[n] = '\0';
		buff = gnl_strjoin(buff, temp);
	}
	free(temp);
	return (buff);
}

char	*get_next_line(int fd)
{
	static char	*buff;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buff = gnl_read(fd, buff);
	if (!buff)
		return (NULL);
	line = gnl_line(buff);
	buff = gnl_buffer(buff);
	return (line);
}
