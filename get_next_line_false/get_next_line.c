/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fharifen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 10:13:18 by fharifen          #+#    #+#             */
/*   Updated: 2024/03/08 16:36:03 by fharifen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

void	fill_line(char **rest, char **line)
{
	int	i;
	int	j;

	if (*rest == NULL)
		return ;
	i = 0;
	j = 0;
	while ((*rest)[i])
	{
		if ((*rest)[i] == '\n')
			break;
		i++;
	}
	*line = ft_substr(*rest, j, i);
	if (*line == NULL)
		return ;
}

void	clean_rest(char **rest)
{
	int		i;
	char	*clean;
	
	clean = malloc(sizeof(char) * ft_strlen(*rest) + 1);
	if (!clean)
		return ;
	i = 0;
	while ((*rest)[i] && (*rest)[i] != '\n')
		i++;
	if ((*rest)[i] && (*rest)[i] == '\n')
		i++;
	clean = ft_substr(*rest, i, (ft_strlen(*rest) - i));
	if (!clean)
		return ;
	free(*rest);
	*rest = clean;
}

void	add_rest(char **rest, char *buf, int ret)
{
	char	*str;
	int		i;

	str = malloc(sizeof(char) * (ret + 1));
	if (!str)
		return ;
	i = 0;
	while (buf[i] && i < ret)
	{
		str[i] = buf[i];
		i++;
	}
	str[i] = '\0';
	*rest = str;
	free(str);
}

void	read_buffer(int fd, char **rest, int *ret_ptr)
{
	char		*buf;

	while (!ft_strchr(*rest) && *ret_ptr != 0)
	{
		buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (!buf)
			return ;
		*ret_ptr = read(fd, buf, BUFFER_SIZE);
		if ((*rest == NULL && *ret_ptr == 0) || *ret_ptr == -1)
		{
			free(buf);
			return ;
		}
		buf[*ret_ptr] = '\0';
		add_rest(rest, buf, *ret_ptr);
		free(buf);
	}

}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*rest;
	int			ret;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	ret = 1;
	line = NULL;
	read_buffer(fd, &rest, &ret);
	if (rest == NULL)
		return (NULL);

	fill_line(&rest, &line);
	if (ret == 0)
		return (NULL);
	clean_rest(&rest);
	if (line[0] == '\0')
	{
		free(rest);
		rest = NULL;
		return (NULL);
	}

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
