/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odroz-ba <odroz-ba@student.42lyon.f>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 14:56:20 by odroz-ba          #+#    #+#             */
/*   Updated: 2021/03/23 18:51:31 by odroz-ba         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	ft_parsing_loop(t_cub *cub, char *path)
{
	int		fd;
	t_line	line;
	int		vr;
	char	flag;

	flag = 1;
	fd = open(path, O_RDONLY);
	line.i = 0;
	vr = 1;
	while (vr)
	{
		vr = get_next_line(fd, &line.ptr);
		if (vr == -1)
		{
			free(line.ptr);
			ft_close(cub, 1, "get_next_line() error");
		}
		if (flag && ft_parsing_criteria(cub, line))
			flag = 0;
		if (!flag)
			ft_parsing_map(cub, line.ptr, line.i++);
		free(line.ptr);
	}
}

int			ft_parsing(char *path, t_cub *cub)
{
	if (ft_malloc_map(cub, path) == -1)
		return (-1);
	ft_parsing_loop(cub, path);
	if (cub->epars != 511 && cub->epars != 1023)
		ft_close(cub, 1, "missing criteria");
	if (ft_check_map(cub, cub->pars->map, cub->player.pos.x, cub->player.pos.y))
		ft_close(cub, 1, "open map");
	ft_malloc_sprite(cub);
	ft_pos_sprite(cub);
	ft_create_plan(cub);
	return (0);
}
