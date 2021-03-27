/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_texture.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odroz-ba <odroz-ba@student.42lyon.f>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 12:11:41 by odroz-ba          #+#    #+#             */
/*   Updated: 2021/03/27 11:48:11 by odroz-ba         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void		ft_agl_sprite(float *ac, float ab, float bc, char flag)
{
	if (flag)
	{
		if (ab >= 0)
			*ac += 0.5;
		else
			*ac = 0.5 - (*ac);
	}
	else if (!ab)
	{
		if (bc < 0)
			*ac = 0.5 - (*ac);
		else
			*ac += 0.5;
	}
	else
	{
		if (ab >= 0)
			*ac = 0.5 - (*ac);
		else
			*ac += 0.5;
	}
}

float			ft_pythagore(t_cub *cub, t_sprite *sprite, float ab, float bc)
{
	float	ac;

	if (ab > 0.5 || ab < -0.5 || bc > 0.5 || bc < -0.5)
		return (-1);
	ac = bc * bc + ab * ab;
	ac = sqrt(ac);
	if (cub->player.pos.y > sprite->pos.y)
		ft_agl_sprite(&ac, ab, bc, 1);
	else
		ft_agl_sprite(&ac, ab, bc, 0);
	return (ac);
}

unsigned int	ft_sprite_texture(t_cub *cub, t_img *img, t_c *pixel, \
	t_sprite *sprite)
{
	t_i_signed		i_img;
	unsigned int	color;
	float			ac;

	i_img.y = (S_S - pixel->z) * img->h / S_S;
	if (i_img.y >= (img->h * S_S) || i_img.y < 0)
		return (0);
	ac = ft_pythagore(cub, sprite, pixel->x - sprite->pos.x, pixel->y - \
		sprite->pos.y);
	if (ac == -1)
		return (0);
	i_img.x = ac * img->w;
	if (i_img.x >= img->w || i_img.x < 0)
		return (0);
	color = img->pixels[i_img.y * (img->s_l / 4) + i_img.x];
	if (!(color >> 24) && color != img->pixels[0])
		return (color);
	return (0);
}
