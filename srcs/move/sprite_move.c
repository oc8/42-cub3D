/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odroz-ba <odroz-ba@student.42lyon.f>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 14:49:32 by odroz-ba          #+#    #+#             */
/*   Updated: 2021/03/16 18:21:25 by odroz-ba         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	ft_check_new_pos_sprite(t_ptr *ptr, t_c new_pos, t_sprite *sprite)
{
	t_i		i_pos;
	t_i		new_pos_i;
	t_i		pos_player;

	new_pos_i.x = (int)new_pos.x;
	new_pos_i.y = (int)new_pos.y;
	i_pos.x = (int)sprite->pos.x;
	i_pos.y = (int)sprite->pos.y;
	if (!(new_pos_i.x < ptr->pars->nbr_map.x && new_pos_i.y < ptr->pars->nbr_map.y &&\
		new_pos_i.x >= 0 && new_pos_i.y >= 0))
		return ;
	if (ptr->pars->map[new_pos_i.y][new_pos_i.x] != '1' &&\
			ptr->pars->map[new_pos_i.y][i_pos.x] != '1' && ptr->pars->map[i_pos.y]\
			[new_pos_i.x] != '1')
	{
		sprite->pos.x = new_pos.x;
		sprite->pos.y = new_pos.y;
	}
	else if (ptr->pars->map[new_pos_i.y][i_pos.x] != '1')
		sprite->pos.y = new_pos.y;
	else if (ptr->pars->map[i_pos.y][new_pos_i.x] != '1')
		sprite->pos.x = new_pos.x;
	pos_player.x = ptr->player.pos.x;
	pos_player.y = ptr->player.pos.y;
	if (new_pos_i.x == pos_player.x && new_pos_i.y == pos_player.y)
		ptr->nbr_life -= (int)(100 * ptr->delta);
}
