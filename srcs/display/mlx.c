/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odroz-ba <odroz-ba@student.42lyon.f>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 16:18:37 by odroz-ba          #+#    #+#             */
/*   Updated: 2021/03/25 15:19:12 by odroz-ba         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_img	ft_init_img(t_cub *cub, char *path)
{
	t_img	img;

	img.ptr = mlx_xpm_file_to_image(cub->mlx.ptr, path, &img.w, &img.h);
	if (!img.ptr)
		ft_close(cub, 1, "mlx_xpm_file_to_image() error");
	img.pixels = (unsigned int *)mlx_get_data_addr(img.ptr, &img.bpp, \
		&img.s_l, &img.endian);
	ft_add_to_lst(cub, img.ptr);
	return (img);
}

void			ft_mlx_init(t_cub *cub)
{
	cub->mlx.ptr = mlx_init();
	cub->mlx.win = mlx_new_window(cub->mlx.ptr, cub->scr.w, \
		cub->scr.h, "cub3d");
	mlx_mouse_move(cub->mlx.win, cub->scr.w * 0.5, cub->scr.h * 0.5);
	mlx_hook(cub->mlx.win, 6, 1L << 6, ft_mouse, cub);
	mlx_hook(cub->mlx.win, 2, 1L << 0, ft_key, cub);
	mlx_hook(cub->mlx.win, 3, 1L << 1, ft_key_release, cub);
	mlx_hook(cub->mlx.win, 17, 0, ft_quit_x, cub);
	mlx_mouse_hide();
	cub->no = ft_init_img(cub, cub->pars->path_no);
	cub->so = ft_init_img(cub, cub->pars->path_so);
	cub->we = ft_init_img(cub, cub->pars->path_we);
	cub->ea = ft_init_img(cub, cub->pars->path_ea);
	cub->sprite = ft_init_img(cub, cub->pars->path_sprite);
	cub->sky = ft_init_img(cub, "textures/skybox.xpm");
	cub->floor = ft_init_img(cub, "textures/floor.xpm");
	cub->win = ft_init_img(cub, "textures/win.xpm");
	cub->scr.ptr = mlx_new_image(cub->mlx.ptr, cub->scr.w, cub->scr.h);
	cub->scr.pixels = (unsigned int *)mlx_get_data_addr(cub->scr.ptr, \
		&cub->scr.bpp, &cub->scr.s_l, &cub->scr.endian);
}
