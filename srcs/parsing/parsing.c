/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odroz-ba <odroz-ba@student.42lyon.f>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 14:56:20 by odroz-ba          #+#    #+#             */
/*   Updated: 2021/03/29 17:34:46 by odroz-ba         ###   ########lyon.fr   */
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
	if (close(fd))
		ft_close(cub, 1, "close() error");

	printf("\n");
	line.i = -1; //////
	while (++line.i < cub->pars->nbr_map.y) //////
	{
		unsigned int j = -1;
		while (++j < cub->pars->nbr_map.x)
			printf("%c", cub->pars->map[line.i][j]); //////
		printf("\n");
	}
	printf("\n");

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

unsigned int i;
	printf("\n");
	i = -1; //////
	while (++i < cub->pars->nbr_map.y) //////
	{
		unsigned int j = -1;
		while (++j < cub->pars->nbr_map.x)
		{
			if (!cub->pars->map[i][j])
				printf("O");
			else if (cub->pars->map[i][j] == 2)
				printf("2");
			else
				printf("%c", cub->pars->map[i][j]); //////
		}
		printf("\n");
	}
	printf("\n");

	ft_malloc_sprite(cub);
	ft_pos_sprite(cub);
	ft_create_plan(cub);
	return (0);
}
