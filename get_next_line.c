/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 16:18:24 by akdovlet          #+#    #+#             */
/*   Updated: 2026/05/20 09:21:39 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*read_to_newline(int fd, char *buffer)
{
	char		*tmp;
	ssize_t		i;

	tmp = NULL;
	if (buffer[0])
	{
		tmp = ak_strjoin(tmp, buffer);
		if (!tmp)
		{
			buffer[0] = 0;
			return (NULL);
		}
	}
	while (ak_strchr(buffer, '\n') == -1)
	{
		i = read(fd, buffer, BUFFER_SIZE);
		if (i <= 0)
			break ;
		buffer[i] = 0;
		tmp = ak_strjoin(tmp, buffer);
		if (!tmp)
			return (NULL);
	}
	return (tmp);
}

void	clean_static(char *buffer)
{
	int	j;
	int	i;

	j = 0;
	i = 0;
	if (!buffer)
		return ;
	while (buffer[j] != '\n' && buffer[j])
		j++;
	if (buffer[j] == '\n')
		j++;
	while (buffer[j])
		buffer[i++] = buffer[j++];
	buffer[i] = 0;
}

char	*extract_line(char *tmp)
{
	char	*line;
	int		i;

	i = 0;
	if (!tmp)
		return (NULL);
	while (tmp[i] != '\n' && tmp[i])
		i++;
	if (tmp[i] == '\n')
		i++;
	line = malloc(sizeof(char) * (i + 1));
	if (!line)
		return (NULL);
	i = 0;
	while (tmp[i] != '\n' && tmp[i])
	{
		line[i] = tmp[i];
		i++;
	}
	if (tmp[i] == '\n')
		line[i++] = '\n';
	line[i] = 0;
	return (line);
}

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1];
	char		*tmp;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	tmp = read_to_newline(fd, buffer);
	if (!tmp)
		return (NULL);
	line = extract_line(tmp);
	free(tmp);
	clean_static(buffer);
	return (line);
}

#include <stdio.h>

int main()
{
	char *line;
	int i = 0;
	int fd = open("Auden.txt", O_RDONLY);
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		// printf("%d", i);
		i++;
		printf("%s", line);
		free(line);
	}
	close(fd);
}
