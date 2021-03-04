/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odroz-ba <odroz-ba@student.42lyon.f>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 14:31:48 by odroz-ba          #+#    #+#             */
/*   Updated: 2021/03/04 18:32:23 by odroz-ba         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

int		ft_loop(t_ptr *ptr)
{
	float	new_pos_x;
	float	new_pos_y;
	t_i		pos;
	t_i		new_pos;

	new_pos_x = ptr->pos.x;
	new_pos_y = ptr->pos.y;
	if (ptr->key.al)
		ptr->agl_hor -= 0.1;
	if (ptr->key.ar)
		ptr->agl_hor += 0.1;
	if (ptr->key.w)
	{
		// printf("dir : x = %f, y = %f\n", ptr->dir.x, ptr->dir.y);
		// printf("pos : x = %f, y = %f\n\n", ptr->pos.x, ptr->pos.y);
		// printf("pos :\nx = %f, y = %f\n", ptr->pos.x, ptr->pos.y);
		new_pos_x += sin(ptr->agl_hor) * ptr->speed;
		new_pos_y -= cos(ptr->agl_hor) * ptr->speed;
		// printf("x = %f, y = %f\n\n", new_pos_x, new_pos_y);
	}
	if (ptr->key.s)
	{
		// printf("dir :\nx = %f, y = %f\n\n", ptr->dir->x, ptr->dir->y);
		new_pos_x -= sin(ptr->agl_hor) * ptr->speed;
		new_pos_y += cos(ptr->agl_hor) * ptr->speed;
	}
	if (ptr->key.a)
	{
		new_pos_x += sin(ptr->agl_hor - M_PI_2) * ptr->speed;
		new_pos_y -= cos(ptr->agl_hor - M_PI_2) * ptr->speed;
	}
	if (ptr->key.d)
	{
		new_pos_x += sin(ptr->agl_hor + M_PI_2) * ptr->speed;
		new_pos_y -= cos(ptr->agl_hor + M_PI_2) * ptr->speed;
	}
	if (ptr->key.ad)
		ptr->agl_vrt += 0.05;
	if (ptr->key.au)
		ptr->agl_vrt -= 0.05;
	if (ptr->key.up)
		ptr->pos.z += 0.5;
	if (ptr->key.down)
		ptr->pos.z -= 0.5;
	new_pos.x = (int)new_pos_x;
	new_pos.y = (int)new_pos_y;
	pos.x = (int)ptr->pos.x;
	pos.y = (int)ptr->pos.y;
	if (ft_in_map(ptr, new_pos))
	{
		if (ptr->pars->map[new_pos.y][new_pos.x] == 0 || ptr->pos.z > 1 || ptr->pos.z < -0.5)
		{
			ptr->pos.x = new_pos_x;
			ptr->pos.y = new_pos_y;
		}
		else if (ptr->pars->map[new_pos.y][pos.x] == 0)
			ptr->pos.y = new_pos_y;
		else if (ptr->pars->map[pos.y][new_pos.x] == 0)
			ptr->pos.x = new_pos_x;
		ft_create_plan_sprite(ptr);
	}
	else if (ptr->pos.x != new_pos_x || ptr->pos.y != new_pos_y)
	{
		ptr->pos.x = new_pos_x;
		ptr->pos.y = new_pos_y;
		ft_create_plan_sprite(ptr);
	}
	ft_edit_img(ptr);
	return (0);
}

int		ft_init_struct(t_ptr *ptr)
{
	ptr->epars = 0;
	ptr->screen.ptr = 0;
	ptr->speed = 0.5;
	ptr->pars->nbr_sprite = 0;
	return (0);
}

static int	ft_error_arg(int nbr)
{
	if (nbr == 1)
		printf("nbr arg error\n");
	else if (nbr == 2)
		printf("arg error\n");
	else if (nbr == 3)
		printf("\".cub\" error\n");
	else if (nbr == 4)
		printf("\"--save\" error\n");
	return (1);
}

int		ft_check_args(int argc, char *argv[])
{
	int		i;
	int		j;
	char	*str;

	if (argc != 2 && argc != 3)
		return (ft_error_arg(1));
	i = ft_strlen(argv[1]);
	str = ".cub";
	if (i < 4)
	{
		return (ft_error_arg(2));
	}
	j = 4;
	while (j)
		if (argv[1][--i] != str[--j])
			return (ft_error_arg(3));
	if (argc == 3 && ft_strncmp(argv[2], "--save", 7))
		return (ft_error_arg(4));
	if (argc == 3)
		;
	return (0);
}

t_img	ft_init_img(t_ptr *ptr, char *path)
{
	t_img	img;

	img.ptr = mlx_xpm_file_to_image(ptr->mlx.ptr, path, &img.width, &img.height);
	img.pixels = (unsigned int *)mlx_get_data_addr(img.ptr, &img.bpp, &img.s_l, &img.endian);
	return (img);
}

int		main(int argc, char *argv[])
{
	float	fov;
	t_ptr	*ptr;
	int		x;
	int		y;

	if (ft_check_args(argc, argv))
		return (1);
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
		// mlx_destroy_image(mlx.mlx, image_front);
	ptr->mlx.window = mlx_new_window(ptr->mlx.ptr, ptr->mlx.width, ptr->mlx.height, "Cub3D");
	mlx_mouse_move(ptr->mlx.window, ptr->mlx.width * 0.5, ptr->mlx.height * 0.5);
	mlx_hook(ptr->mlx.window, 6, 1L << 6, ft_mouse, ptr);
	mlx_hook(ptr->mlx.window, 2, 1L << 0, ft_key, ptr);
	mlx_hook(ptr->mlx.window, 3, 1L << 1, ft_key_release, ptr);
	mlx_hook(ptr->mlx.window, 17, 0, ft_quit_x, ptr);
	mlx_mouse_hide();

	ptr->no = ft_init_img(ptr, ptr->pars->path_no);
	ptr->so = ft_init_img(ptr, ptr->pars->path_so);
	ptr->we = ft_init_img(ptr, ptr->pars->path_we);
	ptr->ea = ft_init_img(ptr, ptr->pars->path_ea);
	ptr->sprite = ft_init_img(ptr, ptr->pars->path_sprite);
	ptr->sky = ft_init_img(ptr, "textures/skybox.xpm");

	ptr->screen.ptr = mlx_new_image(ptr->mlx.ptr, ptr->mlx.width, ptr->mlx.height);
	ptr->screen.pixels = (unsigned int *)mlx_get_data_addr(ptr->screen.ptr, &ptr->screen.bpp, &ptr->screen.s_l, &ptr->screen.endian);
	fov = 100 * (M_PI / 180);
	ptr->fov_x = 2 * tan(fov / 2);
	ptr->fov_y = 2 * tan(fov * ptr->mlx.height / ptr->mlx.width * 0.5);
	ptr->dir = ft_check_calloc(ptr, ptr->mlx.height * ptr->mlx.width, sizeof(t_c));
	y = -1;
	while (++y < ptr->mlx.height)
	{
		x = -1;
		while (++x < ptr->mlx.width)
		{
			ptr->dir[y * ptr->mlx.width + x].x = ptr->fov_x / ptr->mlx.width * (x - ptr->mlx.width * 0.5);
			ptr->dir[y * ptr->mlx.width + x].y = -1;
			ptr->dir[y * ptr->mlx.width + x].z = - ptr->fov_y / ptr->mlx.height * (y - ptr->mlx.height * 0.5);
		}
	}
	ptr->rs_plans_x = ft_check_calloc(ptr, ptr->pars->nbr_map.x, sizeof(float));
	ptr->rs_plans_y = ft_check_calloc(ptr, ptr->pars->nbr_map.y, sizeof(float));
	ft_edit_img(ptr);
	mlx_put_image_to_window(ptr->mlx.ptr, ptr->mlx.window, ptr->screen.ptr, 0, 0);
	mlx_loop_hook(ptr->mlx.ptr, ft_loop, ptr);
	mlx_loop(ptr->mlx.ptr);
	return (0);
}
