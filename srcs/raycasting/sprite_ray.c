/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_ray.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odroz-ba <odroz-ba@student.42lyon.f>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 12:57:13 by odroz-ba          #+#    #+#             */
/*   Updated: 2021/03/16 17:29:35 by odroz-ba         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

float	ft_ray_sprite(t_ptr *ptr, t_vector dir, t_dist *dist)
{
	t_sprite		*p;
	float			rs_dir;
	float			t;
	unsigned int	i;

	i = 0;
	while (i < ptr->pars->nbr_sprite)
	{
		p = &ptr->pars->plans_sprite[i];
		if (p->t > 0)
		{
			rs_dir = p->a * dir.x + p->b * dir.y + p->c * dir.z;
			if (rs_dir)
			{
				t = p->rs / rs_dir;
				if (t > 0)
				{
					dist->color = ft_is_sprite(ptr, &dist->pixel, dir, t, p);
					if (dist->color)
						return (t);
				}
			}
		}
		i++;
	}
	return (0);
}
