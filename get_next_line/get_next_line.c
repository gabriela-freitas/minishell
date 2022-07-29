/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gafreita <gafreita@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/12 09:38:31 by mfreixo-          #+#    #+#             */
/*   Updated: 2022/07/29 19:55:44 by gafreita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_read(int fd, char *buffer)
{
	int	n;

	if (fd < 0)
	{
		free(buffer);
		return (-1);
	}
	n = read(fd, NULL, 0);
	if (n == -1 || BUFFER_SIZE <= 0 || fd < 0)
	{
		free(buffer);
		return (-1);
	}
	else
	{
		n = read(fd, buffer, BUFFER_SIZE);
		if (n == 0)
		{
			free(buffer);
			return (-1);
		}
		buffer[n] = '\0';
		if (n < BUFFER_SIZE)
			return (-2);
	}
	return (n);
}

char	*get_line(int fd)
{
	char	*buffer;
	int		n;
	char	*aux;
	char	*str;

	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	n = ft_read(fd, buffer);
	if (n == -1)
	{
		return (NULL);
	}
	aux = NULL;
	while (n > 0 || n == -2)
	{
		str = ft_strjoin(aux, buffer);
		aux = ft_strdup(str);
		free(str);
		if (ft_newline(aux) != -1)
			break ;
		buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
		n = ft_read(fd, buffer);
		if (n == -2)
		{
			str = ft_strjoin(aux, buffer);
			aux = ft_strdup(str);
			free(str);
			return (aux);
		}
	}
	return (aux);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;
	int			i;
	int			n;

	if (buffer == NULL)
		buffer = get_line(fd);
	if (buffer == NULL)
		return (NULL);
	n = ft_newline(buffer);
	if (n == -1)
		buffer = ft_strjoin(buffer, get_line(fd));
	if (n == -1)
		n = ft_strlen(buffer);
	line = malloc(sizeof(char) * (n + 2));#include <stdio.h>
	buffer = ft_save_buff(buffer, i);
	return (line);
}
