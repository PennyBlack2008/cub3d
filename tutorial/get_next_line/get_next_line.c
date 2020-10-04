/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jikang <jikang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/21 19:21:49 by jikang            #+#    #+#             */
/*   Updated: 2020/08/26 14:42:52 by jikang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int							ft_nl_index(char *s)
{
	int						nl_index;

	nl_index = 0;
	while (*s)
	{
		if (*s == '\n')
			return (nl_index);
		s++;
		nl_index++;
	}
	return (-1);
}

int							ft_notnull(char **line, char **buff)
{
	int						nl;
	char					*copy;

	nl = ft_nl_index(*buff);
	if (nl != -1)
	{
		(*buff)[nl] = '\0';
		*line = ft_strdup(*buff);
		copy = ft_strdup(*buff + nl + 1);
		safer_free((void **)&(*buff));
		*buff = ft_strdup(copy);
		safer_free((void **)&(copy));
		return (1);
	}
	return (0);
}

int							ft_readline(char **line, char **buff, char *temp)
{
	int						nl;
	char					*copy;

	if ((nl = ft_nl_index(temp)) != -1)
	{
		temp[nl] = '\0';
		*line = ft_strjoin(*buff, temp);
		copy = ft_strdup(temp + nl + 1);
		safer_free((void **)&(temp));
		safer_free((void **)&(*buff));
		*buff = ft_strdup(copy);
		safer_free((void **)&(copy));
		return (1);
	}
	copy = ft_strjoin(*buff, temp);
	free(*buff);
	*buff = copy;
	return (0);
}

int							get_next_line(int fd, char **line)
{
	static char				*buff[OPEN_MAX];
	char					*temp;
	int						n;

	if (fd < 0 || !line || BUFFER_SIZE <= 0)
		return (-1);
	if (buff[fd] == NULL)
		buff[fd] = ft_strdup("\0");
	if (ft_strlen(buff[fd]) != 0 && ft_notnull(line, &buff[fd]))
		return (1);
	temp = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	while ((n = read(fd, temp, BUFFER_SIZE)) > 0)
	{
		temp[n] = '\0';
		if (ft_readline(line, &buff[fd], temp) == 1)
			return (1);
	}
	*line = ft_strdup(buff[fd]);
	safer_free((void **)&(buff[fd]));
	safer_free((void **)&(temp));
	if (n < 0 && safer_free((void **)&(*line)))
		return (-1);
	return (0);
}
