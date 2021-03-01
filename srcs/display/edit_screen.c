/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_screen.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odroz-ba <odroz-ba@student.42lyon.f>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 15:47:07 by odroz-ba          #+#    #+#             */
/*   Updated: 2021/03/01 17:04:18 by odroz-ba         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

/*
** fontion matrice
*/
static t_c	ft_rotation(t_c dir, const t_agl *agl, t_ptr *ptr)
{
	t_c		new;
	t_c		m_z;
	t_c		m_x;

	if (ptr->agl_hor >= M_PI)
		ptr->agl_hor -= 2 * M_PI;
	else if (ptr->agl_hor <= - M_PI)
		ptr->agl_hor += 2 * M_PI;
	m_x.x = dir.x;
	m_x.y = agl->cos_vrt * dir.y - agl->sin_vrt * dir.z;
	m_x.z = agl->sin_vrt * dir.y + agl->cos_vrt * dir.z;
	m_z.x = agl->cos_hor * m_x.x - agl->sin_hor * m_x.y;
	m_z.y = agl->sin_hor * m_x.x + agl->cos_hor * m_x.y;
	m_z.z = m_x.z;
	return (m_z);
}

void	*ft_put_pixels(void *work)
{
	t_ptr	*ptr;
	t_thread	*wptr;
	int		thread_nb;
	int 	x;
	int		y;
	unsigned int	*screen;

	wptr = (t_thread*)work;
	ptr = (t_ptr*)wptr->ptr;
	thread_nb = wptr->id;


	screen = ptr->screen.pixels;
	y = (ptr->mlx.height * 0.25) * thread_nb;
	while (y < (ptr->mlx.height * 0.25) * (thread_nb + 1))
	{
		x = -1;
		while (++x < ptr->mlx.width)
		// {
			screen[y * (ptr->screen.s_l / 4) + x] = ft_ray(ptr, ft_rotation(ptr->dir[y * ptr->mlx.width + x], &ptr->agl, ptr));
		// if (y == x)
		// 	screen[y * (ptr->screen.s_l / 4) + x] = 0x0000000;
		// }
		y++;
	}
	return (ptr);
}

static void	ft_thread(t_ptr *ptr)
{
	t_thread	thread[4];
	int			i;

	i = -1;
	while (++i < 4)
	{
		thread[i] = (t_thread){ptr, i};
		pthread_create(&ptr->thread[i], NULL, &ft_put_pixels, (void*)&thread[i]);
	}
	pthread_join(ptr->thread[0], NULL);
	pthread_join(ptr->thread[1], NULL);
	pthread_join(ptr->thread[2], NULL);
	pthread_join(ptr->thread[3], NULL);
}

static void	ft_before_calc_plans(t_ptr *ptr, float *rs, t_p *plans_1, t_p *plans_2, int nbr)
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

static void	ft_before_calc(t_ptr *ptr, unsigned int *screen)
{
	t_agl	agl;
	
	(void)screen;
	agl.cos_hor = cos(ptr->agl_hor);
	agl.sin_hor = sin(ptr->agl_hor);
	agl.cos_vrt = cos(ptr->agl_vrt);
	agl.sin_vrt = sin(ptr->agl_vrt);
	ptr->agl = agl;
	ft_before_calc_plans(ptr, ptr->rs_plans_y, ptr->pars->plans_so, ptr->pars->plans_no, ptr->pars->nbr_map.y);
	ft_before_calc_plans(ptr, ptr->rs_plans_x, ptr->pars->plans_ea, ptr->pars->plans_we, ptr->pars->nbr_map.x);

}
# include <sys/time.h>
void	ft_edit_img(t_ptr *ptr)
{
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
	// 		printf("sprite : %f %f %f %f\t| x = %d, y = %d\n", p.sprite[j]->a, p.sprite[j]->b, p.sprite[j]->c, p.sprite[j]->d, p.sprite[j]->index.x, p.sprite[j]->index.y);
	// 	printf("\n");
	// }
	// i = -1;
	// while (++i < (ptr->pars->nbr_map.y))
	// {
	// 	p = ptr->pars->plans_so[i];
	// 	printf("plan_so %d : %d %d %d %d\t| nbr = %d\n", i, p.a, p.b, p.c, p.d, p.nbr);
	// 	j = -1;
	// 	while (++j < p.nbr)
	// 		printf("sprite : %f %f %f %f\t| x = %d, y = %d\n", p.sprite[j]->a, p.sprite[j]->b, p.sprite[j]->c, p.sprite[j]->d, p.sprite[j]->index.x, p.sprite[j]->index.y);
	// 	printf("\n");
	// }
	// i = -1;
	// while (++i < (ptr->pars->nbr_map.x))
	// {
	// 	p = ptr->pars->plans_ea[i];
	// 	printf("plan_ea %d : %d %d %d %d\t| nbr = %d\n", i, p.a, p.b, p.c, p.d, p.nbr);
	// 	j = -1;
	// 	while (++j < p.nbr)
	// 		printf("sprite : %f %f %f %f\t| x = %d, y = %d\n", p.sprite[j]->a, p.sprite[j]->b, p.sprite[j]->c, p.sprite[j]->d, p.sprite[j]->index.x, p.sprite[j]->index.y);
	// 	printf("\n");
	// }
	// i = -1;
	// while (++i < (ptr->pars->nbr_map.x))
	// {
	// 	p = ptr->pars->plans_we[i];
	// 	printf("plan_we %d : %d %d %d %d\t| nbr = %d\n", i, p.a, p.b, p.c, p.d, p.nbr);
	// 	j = -1;
	// 	while (++j < p.nbr)
	// 		printf("sprite : %f %f %f %f\t| x = %d, y = %d\n", p.sprite[j]->a, p.sprite[j]->b, p.sprite[j]->c, p.sprite[j]->d, p.sprite[j]->index.x, p.sprite[j]->index.y);
	// 	printf("\n");
	// }
	//
// gettimeofday();
	mlx_sync(MLX_SYNC_WIN_CMD_COMPLETED, ptr->mlx.window);
	mlx_sync(MLX_SYNC_IMAGE_WRITABLE, ptr->screen.ptr);
	ft_before_calc(ptr, ptr->screen.pixels);
	ft_thread(ptr);
	mlx_put_image_to_window(ptr->mlx.ptr, ptr->mlx.window, ptr->screen.ptr, 0, 0);
	// mlx_string_put(ptr->mlx.ptr, ptr->mlx.window, 40, 40, 0xffffff, "FPS");
	mlx_sync(MLX_SYNC_WIN_FLUSH_CMD, ptr->mlx.window);
}
