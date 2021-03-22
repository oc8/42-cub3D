/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_ray.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odroz-ba <odroz-ba@student.42lyon.f>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 15:11:38 by odroz-ba          #+#    #+#             */
/*   Updated: 2021/03/22 14:33:59 by odroz-ba         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	ft_check_index_map(t_ptr *ptr, t_i map)
{
	t_i		*nbr_map;

	nbr_map = &ptr->pars->nbr_map;
	if (ft_in_map(ptr, map))
	{
		if (ptr->pars->map[map.y][map.x] == '1')
			return (1);
	}
	return (0);
}

float	ft_calc_dist(t_plan *p, t_vector dir)
{
	float		rs_dir;
	float		t;

	if (p->d)
	{
		rs_dir = p->a * dir.x + p->b * dir.y + p->c * dir.z;
		if (rs_dir)
		{
			t = p->rs / rs_dir;
			if (t > 0)
				return (t);
		}
	}
	return (0);
}

/*
** rotation matrice
*/
t_vector	ft_rotation(t_vector dir, const t_agl *agl, t_ptr *ptr)
{
	t_vector	m_z;
	t_vector	m_x;

	if (ptr->player.agl_hor >= M_PI)
		ptr->player.agl_hor -= 2 * M_PI;
	else if (ptr->player.agl_hor <= -M_PI)
		ptr->player.agl_hor += 2 * M_PI;
	m_x.x = dir.x;
	m_x.y = agl->cos_vrt * dir.y - agl->sin_vrt * dir.z;
	m_x.z = agl->sin_vrt * dir.y + agl->cos_vrt * dir.z;
	m_z.x = agl->cos_hor * m_x.x - agl->sin_hor * m_x.y;
	m_z.y = agl->sin_hor * m_x.x + agl->cos_hor * m_x.y;
	m_z.z = m_x.z;
	return (m_z);
}

void	ft_ray_screen(t_ptr *ptr)
{
	float	fov_x;
	float	fov_y;
	int		x;
	int		y;
	t_vector	*dir;

	ptr->fov = ptr->fov * M_PI / 180;
	fov_x = 2 * tan(ptr->fov / 2) / ptr->screen.w;
	fov_y = fov_x * ptr->screen.h / ptr->screen.w;
	ptr->player.dir = ft_calloc_lst(ptr, ptr->screen.h * ptr->screen.w, sizeof(t_c));
	y = -1;
	while (++y < ptr->screen.h)
	{
		x = -1;
		while (++x < ptr->screen.w)
		{
			dir = &ptr->player.dir[y * ptr->screen.w + x];
			dir->x = fov_x * (x - ptr->screen.w * 0.5);
			dir->y = -1;
			dir->z = -fov_y * (y - ptr->screen.h * 0.5);
		}
	}
}