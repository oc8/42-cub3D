/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_move_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odroz-ba <odroz-ba@student.42lyon.f>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 14:54:06 by odroz-ba          #+#    #+#             */
/*   Updated: 2021/03/29 14:54:38 by odroz-ba         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_pos_in_skybox(t_cub *cub, t_c new_pos)
{
	float	map;
	t_c		*pos;

	pos = &cub->player.pos;
	map = 10 * cub->pars->nbr_map.x;
	if (new_pos.x > -map && new_pos.x < map)
		pos->x = new_pos.x;
	if (new_pos.y > -map && new_pos.y < map)
		pos->y = new_pos.y;
	if (new_pos.z > -map && new_pos.z < map)
		pos->z = new_pos.z;
}
