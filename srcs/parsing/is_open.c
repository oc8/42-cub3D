/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_open.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odroz-ba <odroz-ba@student.42lyon.f>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 18:34:49 by odroz-ba          #+#    #+#             */
/*   Updated: 2021/03/30 13:15:56 by odroz-ba         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	ft_print_map(t_cub *cub, char **map)
{
	unsigned int j;
	unsigned int i;

	j = -1;
	while (++j < cub->pars->nbr_map.y)
	{
		i = -1;
		while (++i < cub->pars->nbr_map.x)
		{
			if (!map[j][i])
				printf("c");
			else if (map[j][i] == 2)
				printf("2");
			else
				printf("%c", map[j][i]);
		}
		printf("\n");
	}
	usleep(2500);
	printf("\n");
}

static void	ft_check_c(t_cub *cub, char **map, int j, int i)
{
	char	*c;

	c = &map[j][i];
	if (*c == '1' || *c == 0 || *c == 2)
		return ;
	if (*c == '2')
		*c = 2;
	else if (*c == '0')
		*c = 0;
	else
		ft_close(cub, 1, "extra caracter in the map");
	ft_check_map(cub, map, i, j);
}

char		ft_check_map(t_cub *cub, char **map, int i, int j)
{
	if (i - 1 < 0 || i + 1 >= (int)cub->pars->nbr_map.x)
		ft_close(cub, 1, "open map");
	if (j - 1 < 0 || j + 1 >= (int)cub->pars->nbr_map.y)
		ft_close(cub, 1, "open map");
	ft_print_map(cub, map);
	ft_check_c(cub, map, j, i - 1);
	ft_check_c(cub, map, j, i + 1);
	ft_check_c(cub, map, j - 1, i);
	ft_check_c(cub, map, j + 1, i);
	ft_check_c(cub, map, j - 1, i - 1);
	ft_check_c(cub, map, j + 1, i + 1);
	ft_check_c(cub, map, j - 1, i + 1);
	ft_check_c(cub, map, j + 1, i - 1);
	return (0);
}

