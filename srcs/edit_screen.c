/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_screen.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odroz-ba <odroz-ba@student.42lyon.f>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 15:47:07 by odroz-ba          #+#    #+#             */
/*   Updated: 2021/02/13 15:26:57 by odroz-ba         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

/*
** fontion matrice
*/
static t_c	ft_rotation(t_c dir, const t_agl *agl, t_ptr *ptr)
{
	t_c		new;
	// t_c		new2;

	(void)ptr;
	// dir.y = ptr->agl_hor;
	new.x = agl->cos_hor * dir.x - agl->sin_hor * dir.y;
	new.y = agl->cos_vrt * agl->sin_hor * dir.x + agl->cos_vrt * agl->cos_hor * dir.y - agl->sin_vrt * dir.z;
	new.z = agl->sin_vrt * agl->sin_hor * dir.x + agl->sin_vrt * agl->cos_hor * dir.y + agl->cos_vrt * dir.z;

	// new.x = cos.x *dir.x - sin.x * dir.y;
	// new.y = sin.x * dir.x + cos.x * dir.y;
	// new.z = dir.z;

	// new2.y = cos.z * dir.y - sin.z * dir.z;
	// new2.z = sin.z * dir.y + cos.z * dir.z;

	return (new);
}

// static	float	*ft_before_calc(t_ptr *ptr, t_p *plans, int nbr)
// {
// 	float	*rs;
// 	int		i;

// 	rs = ft_check_calloc(ptr, nbr, sizeof(float));
// 	i = -1;
// 	while (++i < nbr)
// 		rs[i] = - (plans[i].a * ptr->pos.x + plans[i].b * ptr->pos.y + plans[i].c * ptr->pos.z + plans[i].d);
// 	return (rs);
// }

static void	ft_put_pixels(t_ptr *ptr, unsigned int *screen)
{
	int		i;
	int		j;
	t_agl	agl;
	t_axe	axe;

	agl.cos_hor = cos(ptr->agl_hor);
	agl.sin_hor = sin(ptr->agl_hor);
	agl.cos_vrt = cos(ptr->agl_vrt);
	agl.sin_vrt = sin(ptr->agl_vrt);
	// axe.rs_plans_x = ft_before_calc(ptr, ptr->pars->plans_x, ptr->pars->nbr_map.x);
	// ptr->emalloc |= e_rs_x;
	// // ft_before_calc(ptr, ptr->pars->plans_so, ptr->pars->nbr_map.x, e_rs_so);
	// axe.rs_plans_y = ft_before_calc(ptr, ptr->pars->plans_ea, ptr->pars->nbr_map.y);
	// ptr->emalloc |= e_rs_y;
	// ft_before_calc(ptr, ptr->pars->plans_we, ptr->pars->nbr_map.y, e_rs_we);
	j = -1;
	while (++j < ptr->mlx.height)
	{
		i = -1;
		while (++i < ptr->mlx.width)
			screen[j * ptr->mlx.width + i] = ft_ray(ptr, ft_rotation(ptr->dir[j * ptr->mlx.width + i], &agl, ptr), &axe);
	}
	// free(axe.rs_plans_x);
	// ptr->emalloc &= e_rs_x;
	// free(axe.rs_plans_y);
	// ptr->emalloc &= e_rs_y; // & ?			mettre dans ft_close
}

void	ft_edit_img(t_ptr *ptr)
{
	static int	nbr = 1;

	ft_create_plan_sprite(ptr);

	// //
	// int		i;
	// unsigned int j;
	// t_p		p;
	// i = -1;
	// while (++i < (ptr->pars->nbr_map.y))
	// {
	// 	p = ptr->pars->plans_no[i];
	// 	printf("plan_no %d : %d %d %d %d\t| nbr = %d\n", i, p.a, p.b, p.c, p.d, p.nbr);
	// 	j = -1;
	// 	while (++j < p.nbr)
	// 		printf("sprite : %d %d %d %d\t| x = %d, y = %d\n", p.sprite[j]->a, p.sprite[j]->b, p.sprite[j]->c, p.sprite[j]->d, p.sprite[j]->index.x, p.sprite[j]->index.y);
	// 	printf("\n");
	// }
	// i = -1;
	// while (++i < (ptr->pars->nbr_map.y))
	// {
	// 	p = ptr->pars->plans_so[i];
	// 	printf("plan_so %d : %d %d %d %d\t| nbr = %d\n", i, p.a, p.b, p.c, p.d, p.nbr);
	// 	j = -1;
	// 	while (++j < p.nbr)
	// 		printf("sprite : %d %d %d %d\t| x = %d, y = %d\n", p.sprite[j]->a, p.sprite[j]->b, p.sprite[j]->c, p.sprite[j]->d, p.sprite[j]->index.x, p.sprite[j]->index.y);
	// 	printf("\n");
	// }
	// i = -1;
	// while (++i < (ptr->pars->nbr_map.x))
	// {
	// 	p = ptr->pars->plans_ea[i];
	// 	printf("plan_ea %d : %d %d %d %d\t| nbr = %d\n", i, p.a, p.b, p.c, p.d, p.nbr);
	// 	j = -1;
	// 	while (++j < p.nbr)
	// 		printf("sprite : %d %d %d %d\t| x = %d, y = %d\n", p.sprite[j]->a, p.sprite[j]->b, p.sprite[j]->c, p.sprite[j]->d, p.sprite[j]->index.x, p.sprite[j]->index.y);
	// 	printf("\n");
	// }
	// i = -1;
	// while (++i < (ptr->pars->nbr_map.x))
	// {
	// 	p = ptr->pars->plans_we[i];
	// 	printf("plan_we %d : %d %d %d %d\t| nbr = %d\n", i, p.a, p.b, p.c, p.d, p.nbr);
	// 	j = -1;
	// 	while (++j < p.nbr)
	// 		printf("sprite : %d %d %d %d\t| x = %d, y = %d\n", p.sprite[j]->a, p.sprite[j]->b, p.sprite[j]->c, p.sprite[j]->d, p.sprite[j]->index.x, p.sprite[j]->index.y);
	// 	printf("\n");
	// }
	// //

	if (nbr)
	{
		ft_put_pixels(ptr, ptr->screen.pixels);
		nbr = 0;
		mlx_put_image_to_window(ptr->mlx.ptr, ptr->mlx.window, ptr->screen.ptr, 0, 0);
	}
	else
	{
		ft_put_pixels(ptr, ptr->switched.pixels);
		nbr = 1;
		mlx_put_image_to_window(ptr->mlx.ptr, ptr->mlx.window, ptr->switched.ptr, 0, 0); // switched
	}
}
