/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odroz-ba <odroz-ba@student.42lyon.f>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 11:45:08 by odroz-ba          #+#    #+#             */
/*   Updated: 2021/03/10 14:50:34 by odroz-ba         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_check_end_of_line(char *buf)
{
	ssize_t		i;

	i = 0;
	while (buf[i] && buf[i] != '\n')
		i++;
	if (buf[i] == '\n')
	{
		buf[i] = '\0';
		return (++i);
	}
	return (0);
}

int			ft_new_buf(char *buf, int i)
{
	ssize_t		j;

	j = -1;
	while (buf[i])
		buf[++j] = buf[i++];
	buf[++j] = '\0';
	return (1);
}

int			ft_error(char **line)
{
	free(*line);
	(*line) = malloc(1);
	return (-1);
}

static int	ft_switch(char **line, char *buf)
{
	char		*temp;

	temp = *line;
	if (!(*line = ft_strjoin(*line, buf)))
		return (ft_error(line));
	free(temp);
	return (0);
}

int			get_next_line(int fd, char **line)
{
	static char	buf[BUFFER_SIZE + 1];
	ssize_t		size;
	ssize_t		flag;

	if (BUFFER_SIZE < 1 || fd < 0 || !line)
		return (-1);
	if ((*line = ft_calloc(1, 1)) == NULL)
		return (-1);
	size = 1;
	while (size != -1 && size != 0)
	{
		flag = ft_check_end_of_line(buf);
		if (ft_switch(line, buf) == -1)
			return (-1);
		if (!flag)
			size = read(fd, buf, BUFFER_SIZE);
		else
			return (ft_new_buf(buf, flag));
		if (size >= 0)
			buf[size] = '\0';
	}
	if (size == -1)
		ft_error(line);
	return (size);
}
