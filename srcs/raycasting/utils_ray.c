/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_ray.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odroz-ba <odroz-ba@student.42lyon.f>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 15:11:38 by odroz-ba          #+#    #+#             */
/*   Updated: 2021/03/23 19:06:58 by odroz-ba         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char		ft_check_index_map(t_cub *cub, t_i map)
{
	t_i		*nbr_map;

	nbr_map = &cub->pars->nbr_map;
	if (ft_in_map(cub, map))
	{
		if (cub->pars->map[map.y][map.x] == '1')
			return (1);
	}
	return (0);
}

float		ft_calc_dist(t_plan *p, t_vector dir)
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

t_vector	ft_rotation(t_vector dir, const t_agl *agl, t_cub *cub)
{
	t_vector	m_z;
	t_vector	m_x;

	if (cub->player.agl_hor >= M_PI)
		cub->player.agl_hor -= 2 * M_PI;
	else if (cub->player.agl_hor <= -M_PI)
		cub->player.agl_hor += 2 * M_PI;
	m_x.x = dir.x;
	m_x.y = agl->cos_vrt * dir.y - agl->sin_vrt * dir.z;
	m_x.z = agl->sin_vrt * dir.y + agl->cos_vrt * dir.z;
	m_z.x = agl->cos_hor * m_x.x - agl->sin_hor * m_x.y;
	m_z.y = agl->sin_hor * m_x.x + agl->cos_hor * m_x.y;
	m_z.z = m_x.z;
	return (m_z);
}

void		ft_ray_screen(t_cub *cub)
{
	float		fov_x;
	float		fov_y;
	int			x;
	int			y;
	t_vector	*dir;

	cub->fov = cub->fov * M_PI / 180;
	fov_x = 2 * tan(cub->fov / 2) / cub->screen.w;
	fov_y = fov_x * cub->screen.h / cub->screen.w;
	cub->player.dir = ft_calloc_lst(cub, cub->screen.h * cub->screen.w, \
		sizeof(t_c));
	y = -1;
	while (++y < cub->screen.h)
	{
		x = -1;
		while (++x < cub->screen.w)
		{
			dir = &cub->player.dir[y * cub->screen.w + x];
			dir->x = fov_x * (x - cub->screen.w * 0.5);
			dir->y = -1;
			dir->z = -fov_y * (y - cub->screen.h * 0.5);
		}
	}
}
