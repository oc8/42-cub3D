/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jump.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odroz-ba <odroz-ba@student.42lyon.f>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 11:37:15 by odroz-ba          #+#    #+#             */
/*   Updated: 2021/03/27 17:23:44 by odroz-ba         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_jump(t_cub *cub)
{
	static char		flag = 0;

	if (cub->player.pos.z < S_P + 0.1 && cub->key.space)
		flag = 1;
	if (flag)
		cub->player.pos.z += cub->delta * SPEED;
	if (cub->player.pos.z > S_P * 2)
		flag = 0;
}
