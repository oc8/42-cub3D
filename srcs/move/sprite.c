/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odroz-ba <odroz-ba@student.42lyon.f>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 14:49:32 by odroz-ba          #+#    #+#             */
/*   Updated: 2021/03/15 18:19:27 by odroz-ba         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	ft_check_others_sprite(t_ptr *ptr, t_i new_pos, t_sprite *sprite)
{
	unsigned int	i;
	t_sprite		*p;

	i = 0;
	while (i < ptr->pars->nbr_sprite)
	{
		p = &ptr->pars->plans_sprite[i];
		// printf("pos = %d, new = %d\n", (int)p->pos.y, new_pos.y);
		if (sprite->rs == p->rs)
			;
		if ((int)p->pos.x == new_pos.x && (int)p->pos.y == new_pos.y)
			return (0);
		i++;
	}
	return (1);
}

void	ft_check_new_pos_sprite(t_ptr *ptr, t_c new_pos, t_sprite *sprite)
{
	t_i		i_pos;
	t_i		new_pos_i;

	new_pos_i.x = (int)new_pos.x;
	new_pos_i.y = (int)new_pos.y;
	i_pos.x = (int)sprite->pos.x;
	i_pos.y = (int)sprite->pos.y;
	if (!ft_check_others_sprite(ptr, new_pos_i, sprite))
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
}
