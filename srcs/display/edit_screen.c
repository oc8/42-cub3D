/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_screen.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odroz-ba <odroz-ba@student.42lyon.f>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 15:47:07 by odroz-ba          #+#    #+#             */
/*   Updated: 2021/03/23 16:23:07 by odroz-ba         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	ft_before_calc_plans(t_cub *cub, t_plan *p1, t_plan *p2, int nbr)
{
	int		i;
	t_c		pos;

	pos = cub->player.pos;
	i = -1;
	while (++i < nbr)
	{
		if (p1[i].d)
			p1[i].rs = ft_calc_rs(cub, &p1[i]);
		if (p2[i].d)
			p2[i].rs = ft_calc_rs(cub, &p2[i]);
	}
}

void		ft_before_calc(t_cub *cub)
{
	t_agl	agl;

	agl.cos_hor = cos(cub->player.agl_hor);
	agl.sin_hor = sin(cub->player.agl_hor);
	agl.cos_vrt = cos(cub->player.agl_vrt);
	agl.sin_vrt = sin(cub->player.agl_vrt);
	cub->agl = agl;
	ft_before_calc_plans(cub, cub->pars->plans_so, \
		cub->pars->plans_no, cub->pars->nbr_map.y);
	ft_before_calc_plans(cub, cub->pars->plans_ea, \
		cub->pars->plans_we, cub->pars->nbr_map.x);
}

void		ft_edit_img(t_cub *cub)
{
	char		fps_str[11];
	char		life_str[5];
	static int	count_fps = 0;

	cub->time = ft_time(cub, fps_str, &count_fps);
	if (cub->nbr_life <= 0)
		ft_close(cub, 0, "\033[31mGame Over !");
	mlx_sync(MLX_SYNC_WIN_CMD_COMPLETED, cub->mlx.win);
	mlx_sync(MLX_SYNC_IMAGE_WRITABLE, cub->screen.ptr);
	ft_before_calc(cub);
	ft_threads(cub);
	mlx_put_image_to_window(cub->mlx.ptr, cub->mlx.win, cub->screen.ptr, 0, 0);
	mlx_string_put(cub->mlx.ptr, cub->mlx.win, 15, 20, 0xffffff, fps_str);
	sprintf(life_str, "%d%%", cub->nbr_life);
	mlx_string_put(cub->mlx.ptr, cub->mlx.win, 15, 40, 0xff0000, life_str);
	mlx_sync(MLX_SYNC_WIN_FLUSH_CMD, cub->mlx.win);
	count_fps++;
}
