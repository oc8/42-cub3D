/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odroz-ba <odroz-ba@student.42lyon.f>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 11:17:10 by odroz-ba          #+#    #+#             */
/*   Updated: 2021/03/08 14:34:01 by odroz-ba         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int		ft_key(int key, t_ptr *ptr)
{
	printf("%d\n", key);
	if (key == KEY_AL)
		ptr->key.al = 1;
	else if (key == KEY_AR)
		ptr->key.ar = 1;
	else if (key == KEY_W)
		ptr->key.w = 1;
	else if (key == KEY_S)
		ptr->key.s = 1;
	else if (key == KEY_A)
		ptr->key.a = 1;
	else if (key == KEY_D)
		ptr->key.d = 1;
	else if (key == KEY_AD)
		ptr->key.ad = 1;
	else if (key == KEY_AU)
		ptr->key.au = 1;
	else if (key == KEY_UP)
		ptr->key.up = 1;
	else if (key == KEY_DOWN)
		ptr->key.down = 1;
	else if (key == KEY_MAJ)
		ptr->key.maj = 1;
	else if (key == KEY_ESC)
		ft_close(ptr, 0);
	return (0);
}

float	ft_key_action(char *flag, float rs_1, float rs_2)
{
	if (*flag)
	{
		*flag = 0;
		return (rs_1);
	}
	*flag = 1;
	return (rs_2);
}

int		ft_key_release(int key, t_ptr *ptr)
{
	if (key == KEY_AL)
		ptr->key.al = 0;
	else if (key == KEY_AR)
		ptr->key.ar = 0;
	else if (key == KEY_W)
		ptr->key.w = 0;
	else if (key == KEY_S)
		ptr->key.s = 0;
	else if (key == KEY_A)
		ptr->key.a = 0;
	else if (key == KEY_D)
		ptr->key.d = 0;
	else if (key == KEY_AD)
		ptr->key.ad = 0;
	else if (key == KEY_AU)
		ptr->key.au = 0;
	else if (key == KEY_UP)
		ptr->key.up = 0;
	else if (key == KEY_DOWN)
		ptr->key.down = 0;
	else if (key == KEY_CTRL)
		ptr->pos.z += ft_key_action(&ptr->key.ctrl, 0.2, -0.2); // reduire la vitesse
	else if (key == KEY_MAJ)
		ptr->key.maj = 0;
	return (0);
}

int		ft_mouse(int x, int y, t_ptr *ptr)
{
	// float	rs;
	
	// mlx_mouse_get_pos(ptr->mlx.window, &x, &y);
	// y = -y;
	printf("x = %d, y = %d\n", x, y);
	x -= ptr->mlx.width * 0.5;
	// y -= ptr->mlx.height * 0.5;
	// y *= -1;
	// printf("x = %d, y = %d\n\n", x, y);
	// printf("hor = %f, ver = %f\n", ptr->agl_hor, ptr->agl_vrt);
	ptr->agl_hor += x / (M_PI * 180);
	// rs = ptr->agl_vrt + y / (M_PI * 180);
	// if (rs < M_PI_2 && rs > - M_PI_2)
	// 	ptr->agl_vrt = rs;
	mlx_mouse_get_pos(ptr->mlx.window, &x, &y);
	
	// printf("hor = %f, ver = %f\n\n", ptr->agl_hor, ptr->agl_vrt);
	// printf("x = %d, y = %d\n\n", x, y);
	// ft_edit_img(ptr);
	// ptr->agl_vrt += y / 10;
	// mlx_mouse_move(ptr->mlx.window, ptr->mlx.width / 2, -135);
	mlx_mouse_move(ptr->mlx.window, ptr->mlx.width * 0.5, ptr->mlx.height * 0.5);
	return (0);
}
