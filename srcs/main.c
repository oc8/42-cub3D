/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odroz-ba <odroz-ba@student.42lyon.f>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 14:31:48 by odroz-ba          #+#    #+#             */
/*   Updated: 2021/02/12 17:33:39 by odroz-ba         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

void	ft_close(t_ptr *ptr, int error)
{
	int		i;

	printf("close :\n");
	if (error == 1)
		printf("malloc error\n");
	else if (error == 2)
		printf("error GNL\n");
	else if (error == 3)
		printf("map error\n");
	else if (error == 4)
		printf("mlx error\n");
	if (ptr->screen.ptr)
		mlx_destroy_image(ptr->mlx.ptr, ptr->screen.ptr);
	i = -1;
	if (ptr->emalloc & e_MAP)
	{
		printf("map free\n");
		while (++i < ptr->pars->nbr_map.y)
			free(ptr->pars->map[i]);
		free(ptr->pars->map);
	}
	if (ptr->emalloc & E_PLANS_X)
		free(ptr->pars->plans_x);
	if (ptr->emalloc & E_PLANS_Y)
	{
		printf("plans free\n");
		free(ptr->pars->plans_y);
	}
	if (ptr->emalloc & e_sprite)
	{
		printf("sprite free\n");
		free(ptr->pars->plans_sprite);
	}
	free(ptr);
	exit(0);
}

int		ft_loop(t_ptr *ptr)
{
	float	new_pos_x;
	float	new_pos_y;
	t_i		pos;
	t_i		new_pos;

	new_pos_x = ptr->pos.x;
	new_pos_y = ptr->pos.y;
	if (ptr->key.al)
		ptr->agl_hor -= 0.08;
	else if (ptr->key.ar)
		ptr->agl_hor += 0.08;
	else if (ptr->key.w)
	{
		// printf("dir : x = %f, y = %f\n", ptr->dir.x, ptr->dir.y);
		// printf("pos : x = %f, y = %f\n\n", ptr->pos.x, ptr->pos.y);
		// printf("pos :\nx = %f, y = %f\n", ptr->pos.x, ptr->pos.y);
		new_pos_x += sin(ptr->agl_hor) * ptr->speed;
		new_pos_y -= cos(ptr->agl_hor) * ptr->speed;
		// printf("x = %f, y = %f\n\n", new_pos_x, new_pos_y);
	}
	else if (ptr->key.s)
	{
		// printf("dir :\nx = %f, y = %f\n\n", ptr->dir->x, ptr->dir->y);
		new_pos_x -= sin(ptr->agl_hor) * ptr->speed;
		new_pos_y += cos(ptr->agl_hor) * ptr->speed;
	}
	else if (ptr->key.a)
	{
		new_pos_x += sin(ptr->agl_hor - M_PI_2) * ptr->speed;
		new_pos_y -= cos(ptr->agl_hor - M_PI_2) * ptr->speed;
	}
	else if (ptr->key.d)
	{
		new_pos_x += sin(ptr->agl_hor + M_PI_2) * ptr->speed;
		new_pos_y -= cos(ptr->agl_hor + M_PI_2) * ptr->speed;
	}
	else if (ptr->key.ad)
		ptr->agl_vrt -= 0.05;
	else if (ptr->key.au)
		ptr->agl_vrt += 0.05;
	else if (ptr->key.up)
		ptr->pos.z += 0.5;
	else if (ptr->key.down)
		ptr->pos.z -= 0.5;

	new_pos.x = (int)new_pos_x;
	new_pos.y = (int)new_pos_y;
	pos.x = (int)ptr->pos.x;
	pos.y = (int)ptr->pos.y;
	if (ptr->pars->map[new_pos.y][new_pos.x] != '1')
	{
		ptr->pos.x = new_pos_x;
		ptr->pos.y = new_pos_y;
	}
	else if (ptr->pars->map[new_pos.y][pos.x] != '1')
		ptr->pos.y = new_pos_y;
	else if (ptr->pars->map[pos.y][new_pos.x] != '1')
		ptr->pos.x = new_pos_x;
	ft_edit_img(ptr);
	
	return (0);
}

int		ft_key(int key, t_ptr *ptr)
{
	printf("%d\n", key);
	if (key == KEY_AL)
		ptr->key.al = 1;
	else if (key == KEY_AR)
		ptr->key.ar = 1;
	else if (key == KEY_w)
		ptr->key.w = 1;
	else if (key == KEY_s)
		ptr->key.s = 1;
	else if (key == KEY_a)
		ptr->key.a = 1;
	else if (key == KEY_d)
		ptr->key.d = 1;
	else if (key == KEY_AD)
		ptr->key.ad = 1;
	else if (key == KEY_AU)
		ptr->key.au = 1;
	else if (key == KEY_UP)
		ptr->key.up = 1;
	else if (key == KEY_DOWN)
		ptr->key.down = 1;
	else if (key == KEY_esc)
		ft_close(ptr, 0);
	return (0);
}

int		ft_key_release(int key, t_ptr *ptr)
{
	printf("release = %d\n", key);
	if (key == KEY_AL)
		ptr->key.al = 0;
	else if (key == KEY_AR)
		ptr->key.ar = 0;
	else if (key == KEY_w)
		ptr->key.w = 0;
	else if (key == KEY_s)
		ptr->key.s = 0;
	else if (key == KEY_a)
		ptr->key.a = 0;
	else if (key == KEY_d)
		ptr->key.d = 0;
	else if (key == KEY_AD)
		ptr->key.ad = 0;
	else if (key == KEY_AU)
		ptr->key.au = 0;
	else if (key == KEY_UP)
		ptr->key.up = 0;
	else if (key == KEY_DOWN)
		ptr->key.down = 0;
	return (0);
}

int		ft_mouse(int x, int y, t_ptr *ptr)
{
	printf("x = %d, y = %d\n", x, y);
	x -= ptr->mlx.width / 2;
	y -= ptr->mlx.height / 2;
	printf("x = %d, y = %d\n\n", x, y);
	ptr->agl_hor += x / (3.14 * 180);
	// ptr->agl_vrt += y / (M_PI * 180);
	ft_edit_img(ptr);
	// ptr->agl_vrt += y / 10;
	mlx_mouse_move(ptr->mlx.window, ptr->mlx.width * 0.5, ptr->mlx.height * 0.5);
	return (0);
}

int		ft_init_struct(t_ptr *ptr)
{
	ptr->emalloc = 0;
	ptr->epars = 0;
	ptr->screen.ptr = 0;
	ptr->speed = 0.5;
	ptr->pars->nbr_sprite = 0;
	return (0);
}

int		ft_quit_X(t_ptr *ptr)
{
	ft_close(ptr, 0);
	return (0);
}

int		main(int argc, char *argv[])
{
	float	fov;
	t_ptr	*ptr;
	int		i;
	int		j;
	// t_c	intersection;
	// t_i	index;

	ptr = 0;
	if (argc == 1 || argc > 3)
		return (0);
	// if (argc == 3 && argv[2] == "--save")
	// 	;
	// if (argc == 3 && argv[2] != "--save")
	// 	return (0);
	if (!(ptr = ft_calloc(1, sizeof(t_ptr))))
	{
		printf("malloc error\n");
		return (-1);
	}
	if (!(ptr->pars = ft_calloc(1, sizeof(t_pars))))
	{
		free(ptr);
		printf("malloc error\n");
		return (-1);
	}
	if (ft_init_struct(ptr) == -1)
		return (-1);
	ptr->mlx.ptr = mlx_init();
	ft_parsing(argv[1], ptr);

	// if (image_front)
	// 	mlx_destroy_image(mlx.mlx, image_front);
	ptr->mlx.window = mlx_new_window(ptr->mlx.ptr, ptr->mlx.width, ptr->mlx.height, "Cub3D");
	mlx_hook(ptr->mlx.window, 6, 1L<<6, ft_mouse, ptr);
	mlx_hook(ptr->mlx.window, 2, 1L<<0, ft_key, ptr);
	mlx_hook(ptr->mlx.window, 3, 1L<<1, ft_key_release, ptr);
	mlx_hook(ptr->mlx.window, 17, 0, ft_quit_X, ptr);
	mlx_mouse_hide();
	mlx_mouse_move(ptr->mlx.window, ptr->mlx.width * 0.5, ptr->mlx.height * 0.5);

	ptr->no.ptr = mlx_xpm_file_to_image(ptr->mlx.ptr, ptr->pars->path_no, &ptr->no.width, &ptr->no.height);
	ptr->no.pixels = (unsigned int *)mlx_get_data_addr(ptr->no.ptr, &ptr->no.bpp, &ptr->no.s_l, &ptr->no.endian);
	ptr->so.ptr = mlx_xpm_file_to_image(ptr->mlx.ptr, ptr->pars->path_so, &ptr->so.width, &ptr->so.height);
	ptr->so.pixels = (unsigned int *)mlx_get_data_addr(ptr->so.ptr, &ptr->so.bpp, &ptr->so.s_l, &ptr->so.endian);
	ptr->we.ptr = mlx_xpm_file_to_image(ptr->mlx.ptr, ptr->pars->path_we, &ptr->we.width, &ptr->we.height);
	ptr->we.pixels = (unsigned int *)mlx_get_data_addr(ptr->we.ptr, &ptr->we.bpp, &ptr->we.s_l, &ptr->we.endian);
	ptr->ea.ptr = mlx_xpm_file_to_image(ptr->mlx.ptr, ptr->pars->path_ea, &ptr->ea.width, &ptr->ea.height);
	ptr->ea.pixels = (unsigned int *)mlx_get_data_addr(ptr->ea.ptr, &ptr->ea.bpp, &ptr->ea.s_l, &ptr->ea.endian);
	ptr->sprite.ptr = mlx_xpm_file_to_image(ptr->mlx.ptr, ptr->pars->path_sprite, &ptr->sprite.width, &ptr->sprite.height);
	ptr->sprite.pixels = (unsigned int *)mlx_get_data_addr(ptr->sprite.ptr, &ptr->sprite.bpp, &ptr->sprite.s_l, &ptr->sprite.endian);

//	index = ft_wall(pos, dir, map, &intersection);
	ptr->screen.ptr = mlx_new_image(ptr->mlx.ptr, ptr->mlx.width, ptr->mlx.height);
	ptr->screen.pixels = (unsigned int *)mlx_get_data_addr(ptr->screen.ptr, &ptr->screen.bpp, &ptr->screen.s_l, &ptr->screen.endian);
	ptr->switched.ptr = mlx_new_image(ptr->mlx.ptr, ptr->mlx.width, ptr->mlx.height);
	ptr->switched.pixels = (unsigned int *)mlx_get_data_addr(ptr->switched.ptr, &ptr->switched.bpp, &ptr->switched.s_l, &ptr->switched.endian);
	fov = 60 * (M_PI / 180);
	// printf("fov = %f\n", fov);

	ptr->fov_x = 2 * tan(fov / 2);
	ptr->fov_y = 2 * tan(fov * ptr->mlx.height / ptr->mlx.width * 0.5);
	// printf("fov_x = %f\n", ptr->fov_x);
	// ft_ray(ptr);
	ptr->dir = ft_check_calloc(ptr, ptr->mlx.height * ptr->mlx.width, sizeof(t_c));
	j = -1;
	while (++j < ptr->mlx.height)
	{
		i = -1;
		while (++i < ptr->mlx.width)
		{
			ptr->dir[j * ptr->mlx.width + i].x = ptr->fov_x / ptr->mlx.width * (i - ptr->mlx.width * 0.5);
			ptr->dir[j * ptr->mlx.width + i].y = -1;
			ptr->dir[j * ptr->mlx.width + i].z = ptr->fov_y / ptr->mlx.height * (j - ptr->mlx.height * 0.5);
		}
	}
	ft_edit_img(ptr);

	// i = -1;
	// while (++i < ecran.height)
	// {
	// 	j = -1;
	// 	while (++j < ecran.width)
	// 	{
	// 		ptr->dir.x = fov_x / ecran.width * (i - ecran.width * 0.5);
	// 		ptr->dir.y = -1;
	// 		ptr->dir.z = fov_y / ecran.height * (j - ecran.height * 0.5);
	// 		ecran.pixels[i * ecran.width + j] = ft_ray(ptr);
	// 	}
	// }
	// i = -1;
	// while (++i < (wood.height / dist))
	// {
	// 	j = -1;
	// 	k = 0;
	// 	while (++j < (wood.width / dist))
	// 	{
	// 		img_wood.pixels[i * (wood.width / dist) + j] = wood.pixels[i * (wood.width * dist) + k];
	// 		k += dist;
	// 	}
	// }
	//mlx_put_image_to_window(ptr->mlx.ptr, ptr->mlx.window, img_wood.ptr, 640, 360);
	mlx_put_image_to_window(ptr->mlx.ptr, ptr->mlx.window, ptr->screen.ptr, 0, 0);
	mlx_loop_hook(ptr->mlx.ptr, ft_loop, ptr);
	mlx_loop(ptr->mlx.ptr);
	return (0);
}

	// int i = -1;
	// int 	j;
	// while (++i < 256)
	// {
	// 	j = -1;
	// 	while (++j < 256)
	// 	{
	// 		img[j * 256 + i] = texture[j * 256 + i];
	// 	}
	// }
	//printf("%d\n", s_l);