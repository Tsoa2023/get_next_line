/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fharifen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 10:13:18 by fharifen          #+#    #+#             */
/*   Updated: 2024/03/21 10:54:20 by fharifen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

static char	*split_line(char *line, char *buff)
{
	int		i;
	int		len;
	char	*rest;

	if (line == NULL || !line[0])
		return (free(buff), NULL);
	i = 0;
	while (line[i] != '\n' && line[i] != '\0')
		i++;
	if (line[i] == '\0')
		return (NULL);
	len = ft_strlen(line);
	rest = ft_substr(line, i + 1, len - i);
	if (*rest == '\0')
	{
		free(rest);
		return (NULL);
	}
	i++;
	while (i < len)
		line[i++] = '\0';
	return (rest);
}

static char	*add_line_buffer(int fd, char *rest)
{
	int		read_c;
	char		*buf;

	read_c = 1;
	buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (buf == NULL)
		return (NULL);
	while (!ft_strchr(rest, '\n') && read_c != 0)
	{
		read_c = read(fd, buf, BUFFER_SIZE);
		if (read_c == -1)
		{
			free(buf);
			return (NULL);
		}
		buf[read_c] = '\0';
		rest = ft_strjoin(rest, buf);
	}
	free(buf);
	if (rest[0] == '\0')
	{
		free(rest);
		return (NULL);
	}
	return (rest);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*rest = NULL;

	if (fd == -1 || BUFFER_SIZE <= 0)
		return (NULL);
	line = add_line_buffer(fd, rest);
	rest = split_line(line, rest);
	return (line);
}
