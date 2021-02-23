/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_screen.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odroz-ba <odroz-ba@student.42lyon.f>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 15:47:07 by odroz-ba          #+#    #+#             */
/*   Updated: 2021/02/23 15:45:17 by odroz-ba         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

/*
** fontion matrice
*/
static t_c	ft_rotation(t_c dir, const t_agl *agl, t_ptr *ptr)
{
	t_c		new;
	t_c		hor;
	t_c		vrt;
	// t_c		new2;

	(void)ptr;
	// dir.y = ptr->agl_hor;


	if (ptr->key.m % 2 == 0)
	{
		new.x = agl->cos_hor * dir.x - agl->sin_hor * dir.y;
		new.y = agl->cos_vrt * agl->sin_hor * dir.x + agl->cos_vrt * agl->cos_hor * dir.y - agl->sin_vrt * dir.z;
		new.z = agl->sin_vrt * agl->sin_hor * dir.x + agl->sin_vrt * agl->cos_hor * dir.y + agl->cos_vrt * dir.z;
	}
	else
	{
		hor.x = agl->cos_hor * dir.x - agl->sin_hor * dir.y;
		hor.y = agl->sin_hor * dir.x + agl->cos_hor * dir.y;
		hor.z = dir.z;
		vrt.x = dir.x;
		vrt.y = agl->cos_vrt * dir.y - agl->sin_vrt * dir.z;
		vrt.z = agl->sin_vrt * dir.y + agl->cos_vrt * dir.z;
		new.x = hor.x * vrt.x;
		new.y = hor.y * vrt.y;
		new.z = hor.z * vrt.z;
	}

	return (new);
}

static void	ft_before_calc(t_ptr *ptr, float *rs, t_p *plans_1, t_p *plans_2, int nbr)
{
	int		i;

	i = -1;
	while (++i < nbr)
	{
		if (plans_1[i].d)
			rs[i] = - (plans_1[i].a * ptr->pos.x + plans_1[i].b * ptr->pos.y + plans_1[i].c * ptr->pos.z + plans_1[i].d);
		else if (plans_2[i].d)
			rs[i] = - (plans_2[i].a * ptr->pos.x + plans_2[i].b * ptr->pos.y + plans_2[i].c * ptr->pos.z + plans_2[i].d);
	}
}

// static void	ft_put_pixels(t_ptr *ptr, unsigned int *screen)
// {
// 	int		i;
// 	int		j;
// 	t_agl	agl;

// 	agl.cos_hor = cos(ptr->agl_hor);
// 	agl.sin_hor = sin(ptr->agl_hor);
// 	agl.cos_vrt = cos(ptr->agl_vrt);
// 	agl.sin_vrt = sin(ptr->agl_vrt);
// 	ft_before_calc(ptr, ptr->axe.rs_plans_y, ptr->pars->plans_so, ptr->pars->plans_no, ptr->pars->nbr_map.y);
// 	ft_before_calc(ptr, ptr->axe.rs_plans_x, ptr->pars->plans_ea, ptr->pars->plans_we, ptr->pars->nbr_map.x);
// 	j = -1;
// 	while (++j < ptr->mlx.height)
// 	{
// 		i = -1;
// 		while (++i < ptr->mlx.width)
// 			screen[j * ptr->mlx.width + i] = ft_ray(ptr, ft_rotation(ptr->dir[j * ptr->mlx.width + i], &agl, ptr));
// 	}
// }

void	*launch_print(void *work)
{
	t_ptr	*ptr;
	t_thread	*wptr;
	int		thread_nb;
	int		j;
	int 	i;
	unsigned int	*screen;

	wptr = (t_thread*)work;
	ptr = (t_ptr*)wptr->ptr;
	thread_nb = wptr->id;

// dprintf(1, "thread_nb = %d\n", thread_nb);

	// if (thread_nb < 3)
	// {
	// 	pthread_create(&ptr->thread[thread_nb], NULL, &launch_print, (void*)ptr);
	// 	// pthread_join(ptr->thread[thread_nb], NULL);
	// }
	// if (ptr->nbr == 0)
	screen = ptr->screen.pixels;
	// else
		// screen = ptr->switched.pixels;
	
	j = (ptr->mlx.height / 4) * thread_nb;
	while (j < (ptr->mlx.height / 4) * (thread_nb + 1))
	{
		i = -1;
		while (++i < ptr->mlx.width)
			screen[j * ptr->mlx.width + i] = ft_ray(ptr, ft_rotation(ptr->dir[j * ptr->mlx.width + i], &ptr->agl, ptr));
		j++;
	}
	return (ptr);
}

static void	ft_put_pixels(t_ptr *ptr, unsigned int *screen)
{
	t_agl	agl;
	// pthread_t	thread[4];
	
	(void)screen;
	agl.cos_hor = cos(ptr->agl_hor);
	agl.sin_hor = sin(ptr->agl_hor);
	agl.cos_vrt = cos(ptr->agl_vrt);
	agl.sin_vrt = sin(ptr->agl_vrt);
	ptr->agl = agl;
	ft_before_calc(ptr, ptr->rs_plans_y, ptr->pars->plans_so, ptr->pars->plans_no, ptr->pars->nbr_map.y);
	ft_before_calc(ptr, ptr->rs_plans_x, ptr->pars->plans_ea, ptr->pars->plans_we, ptr->pars->nbr_map.x);

	t_thread w0 = (t_thread){ptr, 0};
	pthread_create(&ptr->thread[0], NULL, &launch_print, (void*)&w0);
	t_thread w1 = (t_thread){ptr, 1};
	pthread_create(&ptr->thread[1], NULL, &launch_print, (void*)&w1);
	t_thread w2 = (t_thread){ptr, 2};
	pthread_create(&ptr->thread[2], NULL, &launch_print, (void*)&w2);
	t_thread w3 = (t_thread){ptr, 3};
	pthread_create(&ptr->thread[3], NULL, &launch_print, (void*)&w3);

	pthread_join(ptr->thread[0], NULL);
	pthread_join(ptr->thread[1], NULL);
	pthread_join(ptr->thread[2], NULL);
	pthread_join(ptr->thread[3], NULL);
}

void	ft_edit_img(t_ptr *ptr)
{
	// static int	nbr = 1;

	//ft_create_plan_sprite(ptr);

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

		mlx_sync(MLX_SYNC_WIN_CMD_COMPLETED, ptr->mlx.window);
		mlx_sync(MLX_SYNC_IMAGE_WRITABLE, ptr->screen.ptr);

		ft_put_pixels(ptr, ptr->screen.pixels);
		mlx_put_image_to_window(ptr->mlx.ptr, ptr->mlx.window, ptr->screen.ptr, 0, 0);
		mlx_sync(MLX_SYNC_WIN_FLUSH_CMD, ptr->mlx.window);
	// if (nbr)
	// {
	// 	ft_put_pixels(ptr, ptr->screen.pixels);
	// 	nbr = 0;
	// 	mlx_put_image_to_window(ptr->mlx.ptr, ptr->mlx.window, ptr->screen.ptr, 0, 0);
	// }
	// else
	// {
	// 	ft_put_pixels(ptr, ptr->switched.pixels);
	// 	nbr = 1;
	// 	mlx_put_image_to_window(ptr->mlx.ptr, ptr->mlx.window, ptr->switched.ptr, 0, 0); // switched
	// }
}
