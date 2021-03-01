/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odroz-ba <odroz-ba@student.42lyon.f>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 11:13:27 by odroz-ba          #+#    #+#             */
/*   Updated: 2021/03/01 11:14:57 by odroz-ba         ###   ########lyon.fr   */
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
	if (ptr->emalloc & e_rs_x)
		free(ptr->rs_plans_x);
	if (ptr->emalloc & e_rs_y)
		free(ptr->rs_plans_y);
	free(ptr);
	exit(0);
}

int		ft_quit_X(t_ptr *ptr)
{
	ft_close(ptr, 0);
	return (0);
}