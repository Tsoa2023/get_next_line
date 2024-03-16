/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fharifen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 10:13:18 by fharifen          #+#    #+#             */
/*   Updated: 2024/03/16 17:29:47 by fharifen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*split_line(char *line)
{
	int		i;
	int		len;
	char	*rest;

	if (line == NULL || line[0] == '\0')
		return (NULL);
	i = 0;
	while (line[i] != '\n' && line[i] != '\0')
		i++;
	if (line[i] == '\0' || line[1] == '\0')
		return (NULL);
	rest = ft_substr(line, i + 1, ft_strlen(line) - i);
	i++;
	len = ft_strlen(line);
	while (i < len)
		line[i++] = '\0';
	return (rest);
}

static char	*add_line_buffer(int fd, char *rest, char *buf)
{
	int		read_c;

	read_c = 1;
	while (!ft_strchr(rest, '\n') && read_c != 0)
	{
		read_c = read(fd, buf, BUFFER_SIZE);
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
	char		*buf;
	char		*line;
	static char	*rest;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		free(rest);
		rest = NULL;
		return (NULL);
	}
	buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (NULL);
	line = add_line_buffer(fd, rest, buf);
	buf = NULL;
	if (!line)
		return (NULL);
	rest = split_line(line);
	return (line);
}
