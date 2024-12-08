/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-kass <rel-kass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 22:34:52 by rel-kass          #+#    #+#             */
/*   Updated: 2024/12/07 23:16:21 by rel-kass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int	nline(char *data)
{
	int	i;

	i = 0;
	while (data[i] && data[i] != '\n')
		i++;
	if (data[i] == '\n')
		i++;
	return (i);
}

char	*update_line(char *data)
{
	int		i;
	int		s;
	char	*update;

	s = 0;
	i = nline(data);
	if (!data[i])
		return (free(data), NULL);
	update = ft_calloc(ft_strlen(data) - i + 1, sizeof(char));
	while (data[i])
		update[s++] = data[i++];
	free(data);
	return (update);
}

char	*extract_line(char *data)
{
	char	*line;
	int		i;

	i = nline(data);
	line = ft_calloc(i + 1, sizeof(char));
	ft_memcpy(line, data, i);
	return (line);
}

char	*read_fd(int fd, char *data)
{
	ssize_t		byte;
	char		*tmp;

	if (!data)
		data = ft_calloc(1, 1);
	tmp = ft_calloc((size_t)BUFFER_SIZE + 1, sizeof(char));
	byte = 1;
	while (byte > 0 && !ft_strchr(tmp, '\n'))
	{
		byte = read(fd, tmp, BUFFER_SIZE);
		if (byte < 0)
		{
			free(data);
			free(tmp);
			return (NULL);
		}
		tmp[byte] = '\0';
		data = ft_strjoin(data, tmp);
	}
	free(tmp);
	return (data);
}

char	*get_next_line(int fd)
{
	static char	*data[OPEN_MAX];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd > OPEN_MAX || BUFFER_SIZE > INT_MAX)
		return (NULL);
	data[fd] = read_fd(fd, data[fd]);
	if (!data[fd])
		return (NULL);
	if (nline(data[fd]) == 0)
	{
		free(data[fd]);
		data[fd] = NULL;
		return (NULL);
	}
	line = extract_line(data[fd]);
	data[fd] = update_line(data[fd]);
	return (line);
}
