/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odroz-ba <odroz-ba@student.42lyon.f>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 11:17:10 by odroz-ba          #+#    #+#             */
/*   Updated: 2021/03/23 16:16:41 by odroz-ba         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void		ft_key_move(t_cub *ptr, int key)
{
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
	else if (key == KEY_SPACE)
		ptr->key.space = 1;
}

int				ft_key(int key, t_cub *ptr)
{
	printf("%d\n", key);
	if (key == KEY_M)
		ptr->key.m = 1;
	else if (key == KEY_ESC)
		ft_close(ptr, 0, "\033[34mclose");
	else
		ft_key_move(ptr, key);
	return (0);
}

static float	ft_key_action(char *flag, float rs_1, float rs_2)
{
	if (*flag)
	{
		*flag = 0;
		return (rs_1);
	}
	*flag = 1;
	return (rs_2);
}

int				ft_key_release(int key, t_cub *ptr)
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
		ptr->player.pos.z += ft_key_action(&ptr->key.ctrl, 0.2, -0.2);
	else if (key == KEY_MAJ)
		ptr->key.maj = 0;
	return (0);
}

int				ft_mouse(int x, int y, t_cub *ptr)
{
	float		rs;
	static int	x_temp = 0;
	static int	y_temp = 0;

	if (!x_temp && !y_temp)
	{
		x_temp = x;
		y_temp = y;
		return (0);
	}
	x -= x_temp;
	y -= y_temp - 22;
	ptr->player.agl_hor += x / (M_PI * 180);
	rs = ptr->player.agl_vrt + y / (M_PI * 180);
	if (rs < M_PI_2 && rs > -M_PI_2)
		ptr->player.agl_vrt = rs;
	mlx_mouse_move(ptr->mlx.win, ptr->screen.w * .5, ptr->screen.h * .5);
	mlx_mouse_get_pos(ptr->mlx.win, &x_temp, &y_temp);
	return (0);
}
