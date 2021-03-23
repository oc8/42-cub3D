/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_open.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odroz-ba <odroz-ba@student.42lyon.f>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 18:34:49 by odroz-ba          #+#    #+#             */
/*   Updated: 2021/03/23 18:35:04 by odroz-ba         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	check_c(t_cub *cub, char c)
{
	if (c == '1' || c == 0 || c == 2)
		return (0);
	if (c != '0' && c != '2')
		ft_close(cub, 1, "extra caracter on map");
	return (1);
}

char		ft_check_map(t_cub *cub, char **map, int i, int j)
{
	if (i - 1 < 0 || i + 1 >= (int)cub->pars->nbr_map.x || j - 1 < 0 || \
			j + 1 >= (int)cub->pars->nbr_map.y)
		ft_close(cub, 1, "open map");
	if (map[j][i] != '2')
		map[j][i] = 0;
	else
		map[j][i] = 2;
	if (check_c(cub, map[j][i - 1]) && ft_check_map(cub, map, i - 1, j))
		return (1);
	if (check_c(cub, map[j][i + 1]) && ft_check_map(cub, map, i + 1, j))
		return (1);
	if (check_c(cub, map[j - 1][i]) && ft_check_map(cub, map, i, j - 1))
		return (1);
	if (check_c(cub, map[j + 1][i]) && ft_check_map(cub, map, i, j + 1))
		return (1);
	if (check_c(cub, map[j - 1][i - 1]) && ft_check_map(cub, map, i - 1, j - 1))
		return (1);
	if (check_c(cub, map[j + 1][i + 1]) && ft_check_map(cub, map, i + 1, j + 1))
		return (1);
	if (check_c(cub, map[j - 1][i + 1]) && ft_check_map(cub, map, i + 1, j - 1))
		return (1);
	if (check_c(cub, map[j + 1][i - 1]) && ft_check_map(cub, map, i - 1, j + 1))
		return (1);
	return (0);
}
