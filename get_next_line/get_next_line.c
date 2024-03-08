/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fharifen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 10:13:18 by fharifen          #+#    #+#             */
/*   Updated: 2024/03/08 16:55:01 by fharifen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

char	*fill_line(char *s)
{
	int	i;
	int	j;
	char	*line;

	i = 0;
	j = 0;
	line = ft_strdup("");
	while (s[i])
	{
		if (s[i] == '\n')
			break;
		i++;
	}
	line = ft_substr(s, j, i);
	return (line);
}

char	*fill_rest(char *s)
{
	int	i;
	int	j;
	char	*rest;

	i = 0;
	rest = NULL;
	while (s[i] != '\n')
		i++;
	j = ft_strlen(s) - i;
	rest = ft_substr(s, i + 1, j);
	return (rest);
}

char	*get_next_line(int fd)
{
	char		*buf;
	char		*line;
	char		*tmp;
	static char	*rest;
	int			ret;

	line = ft_strdup("");
	tmp = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!tmp)
		return (NULL);
	buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (rest)
	{
		tmp = ft_strjoin(tmp, rest);
		free(rest);
	}
	while ((ret = read(fd, buf, BUFFER_SIZE)))
	{
		tmp = ft_strjoin(tmp, buf);
		if (ft_strchr(buf, '\n'))
			break;
	}
	line = fill_line(tmp);	
	if (ret == 0)
		return (NULL);
	rest = fill_rest(tmp);	
	return (line);
}

int main(void)
{
	int	fd;
	char *str;

	fd = open("File_toGET", O_RDONLY);
	if (fd == -1)
		printf("Error to open file\n");
	while (1)
	{
		str = get_next_line(fd);
		if (str == NULL)
			break;
		printf("%s\n", str);
		free(str);
	}
	return (0);
}
