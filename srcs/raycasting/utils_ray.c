/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_ray.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odroz-ba <odroz-ba@student.42lyon.f>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 15:11:38 by odroz-ba          #+#    #+#             */
/*   Updated: 2021/03/26 19:03:11 by odroz-ba         ###   ########lyon.fr   */
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

	if (p->d)
	{
		rs_dir = p->a * dir.x + p->b * dir.y + p->c * dir.z;
		if (rs_dir)
		{
			p->t = p->rs / rs_dir;
			if (p->t > 0)
				return (1);
		}
	}
	return (0);
}

t_vector	ft_rotation(t_vector dir, const t_agl *agl)
{
	t_vector	m_z;
	t_vector	m_x;

	m_x.y = agl->cos_vrt * dir.y - agl->sin_vrt * dir.z;
	m_x.z = agl->sin_vrt * dir.y + agl->cos_vrt * dir.z;
	m_z.x = agl->cos_hor * dir.x - agl->sin_hor * m_x.y;
	m_z.y = agl->sin_hor * dir.x + agl->cos_hor * m_x.y;
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

	cub->fov = FOV * M_PI / 180;
	fov_x = 2 * tan(cub->fov / 2) / cub->scr.w;
	fov_y = fov_x * cub->scr.h / cub->scr.w;
	cub->player.dir = ft_calloc_lst(cub, cub->scr.h * cub->scr.w, \
		sizeof(t_c));
	y = -1;
	while (++y < cub->scr.h)
	{
		x = -1;
		while (++x < cub->scr.w)
		{
			dir = &cub->player.dir[y * cub->scr.w + x];
			dir->x = fov_x * (x - cub->scr.w * 0.5);
			dir->y = -1;
			dir->z = -fov_y * (y - cub->scr.h * 0.5);
		}
	}
	cub->player.dir_center = cub->player.dir[cub->scr.h / 2 * \
		(cub->scr.s_l / 4) + cub->scr.w / 2];
}
