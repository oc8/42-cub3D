/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odroz-ba <odroz-ba@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 18:37:25 by odroz-ba          #+#    #+#             */
/*   Updated: 2021/04/04 15:00:03 by odroz-ba         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	ft_check_longest_line(char *line, int *size_line_max)
{
	int			i;
	int			size_line;
	static char	flag = 1;

	i = -1;
	while (line[++i] == ' ')
		;
	if (flag && (line[i] == '1' || line[i] == '0' || line[i] == '2'))
		flag = 0;
	if (!flag)
	{
		size_line = ft_strlen(line);
		if (*size_line_max < size_line)
			*size_line_max = size_line;
		return (1);
	}
	return (0);
}

static void	ft_count(t_cub *cub, char *path, int *count_line, int *s_l_max)
{
	int		fd;
	char	*line;
	int		vr;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		ft_close(cub, 1, "open() error");
	vr = 1;
	*count_line = 0;
	*s_l_max = 0;
	while (vr)
	{
		vr = get_next_line(fd, &line);
		if (vr == -1)
		{
			free(line);
			printf("error GNL\n");
			ft_close(cub, 1, "get_next_line() error");
		}
		*count_line += ft_check_longest_line(line, s_l_max);
		free(line);
	}
	if (close(fd))
		ft_close(cub, 1, "close() error");
}

int			ft_malloc_map(t_cub *cub, char *path)
{
	int		count_line;
	int		size_line_max;
	int		i;

	ft_count(cub, path, &count_line, &size_line_max);
	cub->pars->nbr_map.x = size_line_max;
	cub->pars->nbr_map.y = count_line;
	if (!(cub->pars->map = ft_calloc_lst(cub, count_line, sizeof(char *))))
		return (-1);
	i = -1;
	while (++i < count_line)
	{
		cub->pars->map[i] = ft_calloc_lst(cub, size_line_max, sizeof(char));
		if (!cub->pars->map[i])
			ft_close(cub, 1, "malloc map error");
	}
	return (0);
}
