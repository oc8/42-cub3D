/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_pars.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odroz-ba <odroz-ba@student.42lyon.f>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 14:56:22 by odroz-ba          #+#    #+#             */
/*   Updated: 2021/03/23 16:16:41 by odroz-ba         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	ft_check_c(t_cub *ptr, char c)
{
	if (c == '1' || c == 0 || c == 2)
		return (0);
	if (c != '0' && c != '2')
		ft_close(ptr, 1, "extra caracter on map");
	return (1);
}

char		ft_check_map(t_cub *ptr, char **map, int i, int j)
{
	if (i - 1 < 0 || i + 1 >= (int)ptr->pars->nbr_map.x || j - 1 < 0 || \
			j + 1 >= (int)ptr->pars->nbr_map.y)
		ft_close(ptr, 1, "open map");
	if (map[j][i] != '2')
		map[j][i] = 0;
	else
		map[j][i] = 2;
	if (ft_check_c(ptr, map[j][i - 1]) && ft_check_map(ptr, map, i - 1, j))
			return (1);
	if (ft_check_c(ptr, map[j][i + 1]) && ft_check_map(ptr, map, i + 1, j))
			return (1);
	if (ft_check_c(ptr, map[j - 1][i]) && ft_check_map(ptr, map, i, j - 1))
			return (1);
	if (ft_check_c(ptr, map[j + 1][i]) && ft_check_map(ptr, map, i, j + 1))
			return (1);
	if (ft_check_c(ptr, map[j - 1][i - 1]) && ft_check_map(ptr, map, i - 1, j - 1))
			return (1);
	if (ft_check_c(ptr, map[j + 1][i + 1]) && ft_check_map(ptr, map, i + 1, j + 1))
			return (1);
	if (ft_check_c(ptr, map[j - 1][i + 1]) && ft_check_map(ptr, map, i + 1, j - 1))
			return (1);
	if (ft_check_c(ptr, map[j + 1][i - 1]) && ft_check_map(ptr, map, i - 1, j + 1))
			return (1);
	return (0);
}

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

static void	ft_count(t_cub *ptr, char *path, int *count_line, int *size_line_max)
{
	int		fd;
	char	*line;
	int		vr;

	fd = open(path, O_RDONLY);
	vr = 1;
	*count_line = 0;
	*size_line_max = 0;
	while (vr)
	{
		vr = get_next_line(fd, &line);
		if (vr == -1)
		{
			free(line);
			printf("error GNL\n");
			ft_close(ptr, 1, "get_next_line() error");
		}
		*count_line += ft_check_longest_line(line, size_line_max);
		free(line);
	}
}

int		ft_malloc_map(t_cub *ptr, char *path)
{
	int		count_line;
	int		size_line_max;
	int		i;

	ft_count(ptr, path, &count_line, &size_line_max);
	ptr->pars->nbr_map.x = size_line_max;
	ptr->pars->nbr_map.y = count_line;
	if (!(ptr->pars->map = ft_calloc_lst(ptr, count_line, sizeof(char *))))
		return (-1);
	i = -1;
	while (++i < count_line)
	{
		ptr->pars->map[i] = ft_calloc_lst(ptr, size_line_max, sizeof(char));
		if (!ptr->pars->map[i])
			ft_close(ptr, 1, "malloc map error");
	}
	return (0);
}

static void	ft_first_pos(t_cub *ptr, char c, int i, int j)
{
	if (ptr->epars & e_FIRST_DIR)
		ft_close(ptr, 1, "too many player pos");
	ptr->epars |= e_FIRST_DIR;
	if (c == 'N')
		ptr->player.agl_hor = 0;
	else if (c == 'S')
		ptr->player.agl_hor = M_PI_2 * 2;
	else if (c == 'E')
		ptr->player.agl_hor = M_PI_2;
	else if (c == 'W')
		ptr->player.agl_hor = M_PI_2 * 3;
	ptr->player.agl_vrt = 0;
	ptr->player.pos.x = i + 0.5;
	ptr->player.pos.y = j + 0.5;
	ptr->player.pos.z = 0.5;
	ptr->pars->map[j][i] = '0';
}

void	ft_parsing_map(t_cub *ptr, char *line, int j, t_i *first_pos)
{
	unsigned int	i;

	if (line[0] == '#')
		return ;
	i = -1;
	while (line[++i])
	{
		if (line[i] == '0' || line[i] == '1' || line[i] == '2' || line[i] == ' ')
			ptr->pars->map[j][i] = line[i];
		else if (line[i] == 'N' || line[i] == 'E' || line[i] == 'S' || line[i] == 'W')
		{
			ft_first_pos(ptr, line[i], i, j);
			first_pos->x = i;
			first_pos->y = j;
		}
		else if (line[i] == 'F')
		{
			if (ptr->epars & e_FINISH)
				ft_close(ptr, 1, "too many 'F'");
			ptr->epars |= e_FINISH;
			ptr->pars->finish.x = i;
			ptr->pars->finish.y = j;
			ptr->pars->map[j][i] = '0';
		}
		else
			ft_close(ptr, 1, "extra caracter in the map");
	}
	while (++i < ptr->pars->nbr_map.x)
		ptr->pars->map[j][i] = '0';
}
