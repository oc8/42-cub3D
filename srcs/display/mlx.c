/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odroz-ba <odroz-ba@student.42lyon.f>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 16:18:37 by odroz-ba          #+#    #+#             */
/*   Updated: 2021/03/23 16:16:41 by odroz-ba         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_img	ft_init_img(t_cub *ptr, char *path)
{
	t_img	img;

	img.ptr = mlx_xpm_file_to_image(ptr->mlx.ptr, path, &img.w, &img.h);
	if (!img.ptr)
		ft_close(ptr, 1, "mlx_xpm_file_to_image() error");
	img.pixels = (unsigned int *)mlx_get_data_addr(img.ptr, &img.bpp, \
		&img.s_l, &img.endian);
	ft_add_to_lst(ptr, img.ptr);
	return (img);
}

void			ft_mlx_init(t_cub *ptr)
{
	ptr->mlx.ptr = mlx_init();
	ptr->mlx.win = mlx_new_window(ptr->mlx.ptr, ptr->screen.w, \
		ptr->screen.h, "cub3d");
	mlx_mouse_move(ptr->mlx.win, ptr->screen.w * 0.5, ptr->screen.h * 0.5);
	mlx_hook(ptr->mlx.win, 6, 1L << 6, ft_mouse, ptr);
	mlx_hook(ptr->mlx.win, 2, 1L << 0, ft_key, ptr);
	mlx_hook(ptr->mlx.win, 3, 1L << 1, ft_key_release, ptr);
	mlx_hook(ptr->mlx.win, 17, 0, ft_quit_x, ptr);
	mlx_mouse_hide();
	ptr->no = ft_init_img(ptr, ptr->pars->path_no);
	ptr->so = ft_init_img(ptr, ptr->pars->path_so);
	ptr->we = ft_init_img(ptr, ptr->pars->path_we);
	ptr->ea = ft_init_img(ptr, ptr->pars->path_ea);
	ptr->sprite = ft_init_img(ptr, ptr->pars->path_sprite);
	ptr->sky = ft_init_img(ptr, "textures/skybox.xpm");
	ptr->floor = ft_init_img(ptr, "textures/floor.xpm");
	ptr->screen.ptr = mlx_new_image(ptr->mlx.ptr, ptr->screen.w, ptr->screen.h);
	ptr->screen.pixels = (unsigned int *)mlx_get_data_addr(ptr->screen.ptr, \
		&ptr->screen.bpp, &ptr->screen.s_l, &ptr->screen.endian);
}
