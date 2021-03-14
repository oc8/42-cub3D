/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odroz-ba <odroz-ba@student.42lyon.f>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 14:56:22 by odroz-ba          #+#    #+#             */
/*   Updated: 2021/03/14 18:18:27 by odroz-ba         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int		ft_check_map(t_ptr *ptr, char **map, int i, int j)
{
	if (i - 1 < 0 || i + 1 >= ptr->pars->nbr_map.x || j - 1 < 0 || \
			j + 1 >= ptr->pars->nbr_map.y || map[j][i] == ' ')
		ft_close(ptr, 3);
	if (map[j][i] != '2')
		map[j][i] = 0;
	else
		map[j][i] = 2;
	if ((map[j][i - 1] == '0' || map[j][i - 1] == '2') && ft_check_map(ptr, map, i - 1, j))
			return (1);
	if ((map[j][i + 1] == '0' || map[j][i + 1] == '2') && ft_check_map(ptr, map, i + 1, j))
			return (1);
	if ((map[j - 1][i] == '0' || map[j - 1][i] == '2') && ft_check_map(ptr, map, i, j - 1))
			return (1);
	if ((map[j + 1][i] == '0' || map[j + 1][i] == '2') && ft_check_map(ptr, map, i, j + 1))
			return (1);

	if ((map[j - 1][i - 1] == '0' || map[j - 1][i - 1] == '2') && ft_check_map(ptr, map, i - 1, j - 1))
			return (1);
	if ((map[j + 1][i + 1] == '0' || map[j + 1][i + 1] == '2') && ft_check_map(ptr, map, i + 1, j + 1))
			return (1);
	if ((map[j - 1][i + 1] == '0' || map[j - 1][i + 1] == '2') && ft_check_map(ptr, map, i + 1, j - 1))
			return (1);
	if ((map[j + 1][i - 1] == '0' || map[j + 1][i - 1] == '2') && ft_check_map(ptr, map, i - 1, j + 1))
			return (1);
	return (0);
}

int		ft_malloc_map(t_ptr *ptr, char *path)
{
	int		fd;
	char	*line;
	int		size_line_max;
	int		size_line;
	int		count_line;
	int		i;
	int		vr;
	char	flag;

	size_line_max = 0;
	count_line = 0;
	fd = open(path, O_RDONLY);
	flag = 1;
	vr = 1;
	while (vr)
	{
		vr = get_next_line(fd, &line);
		if (vr == -1)
		{
			free(line);
			printf("error GNL\n");
			ft_close(ptr, 2);
		}
		i = -1;
		while (line[++i] == ' ')
			;
		if (flag && (line[i] == '1' || line[i] == '0' || line[i] == '2'))
			flag = 0;
		if (!flag)
		{
			size_line = ft_strlen(line);
			if (size_line_max < size_line)
				size_line_max = size_line;
			count_line++;
		}
		free(line);
	}
	ptr->pars->nbr_map.x = size_line_max;
	ptr->pars->nbr_map.y = count_line;
	// free(ptr->pars->map);
	if (!(ptr->pars->map = ft_calloc_lst(ptr, count_line, sizeof(char *))))
		return (-1);
	vr = -1;
	while (++vr < count_line)
	{
		ptr->pars->map[vr] = ft_calloc_lst(ptr, size_line_max, sizeof(char));
		if (!ptr->pars->map[vr])
			ft_close(ptr, 1);
	}
	return (0);
}

static void	ft_first_pos(t_ptr *ptr, char c, int i, int j)
{
	if (ptr->epars & e_FIRST_DIR)
		ft_close(ptr, 3);
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

void	ft_parsing_map(t_ptr *ptr, char *line, int j, t_i *first_pos)
{
	int		i;

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
		else
			ft_close(ptr, 3);
	}
	while (i < ptr->pars->nbr_map.x)
		ptr->pars->map[j][i++] = '0';
}
