/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odroz-ba <odroz-ba@student.42lyon.f>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 11:17:10 by odroz-ba          #+#    #+#             */
/*   Updated: 2021/03/25 15:40:34 by odroz-ba         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void		ft_key_move(t_cub *cub, int key)
{
	if (key == KEY_AL)
		cub->key.al = 1;
	else if (key == KEY_AR)
		cub->key.ar = 1;
	else if (key == KEY_W)
		cub->key.w = 1;
	else if (key == KEY_S)
		cub->key.s = 1;
	else if (key == KEY_A)
		cub->key.a = 1;
	else if (key == KEY_D)
		cub->key.d = 1;
	else if (key == KEY_AD)
		cub->key.ad = 1;
	else if (key == KEY_AU)
		cub->key.au = 1;
	else if (key == KEY_UP)
		cub->key.up = 1;
	else if (key == KEY_DOWN)
		cub->key.down = 1;
	else if (key == KEY_MAJ)
		cub->key.maj = 1;
	else if (key == KEY_SPACE)
		cub->key.space = 1;
}

int				ft_key(int key, t_cub *cub)
{
	printf("%d\n", key);
	if (key == KEY_M)
		cub->key.m = 1;
	else if (key == KEY_ESC)
		ft_close(cub, 0, "\033[34mclose");
	else
		ft_key_move(cub, key);
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

static void		ft_key_release_2(int key, t_cub *cub)
{
	if (key == KEY_MAJ)
		cub->key.maj = 0;
	else if (key == KEY_SPACE)
		cub->key.space = 0;
}

int				ft_key_release(int key, t_cub *cub)
{
	if (key == KEY_AL)
		cub->key.al = 0;
	else if (key == KEY_AR)
		cub->key.ar = 0;
	else if (key == KEY_W)
		cub->key.w = 0;
	else if (key == KEY_S)
		cub->key.s = 0;
	else if (key == KEY_A)
		cub->key.a = 0;
	else if (key == KEY_D)
		cub->key.d = 0;
	else if (key == KEY_AD)
		cub->key.ad = 0;
	else if (key == KEY_AU)
		cub->key.au = 0;
	else if (key == KEY_UP)
		cub->key.up = 0;
	else if (key == KEY_DOWN)
		cub->key.down = 0;
	else if (key == KEY_CTRL)
		cub->player.pos.z += ft_key_action(&cub->key.ctrl, 0.2, -0.2);
	else
		ft_key_release_2(key, cub);
	return (0);
}
