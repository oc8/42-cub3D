/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odroz-ba <odroz-ba@student.42lyon.f>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 11:13:27 by odroz-ba          #+#    #+#             */
/*   Updated: 2021/03/16 18:15:34 by odroz-ba         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	ft_close(t_ptr *ptr, int error)
{
	if (error > 0)
		printf("\033[31mError\n");
	if (error == -1)
		printf("\033[31mGame Over\n");
	if (error == 1)
		printf("malloc error\n");
	else if (error == 2)
		printf("error GNL\n");
	else if (error == 3)
		printf("map error\n");
	else if (error == 4)
		printf("mlx error\n");
	else if (error == 5)
		printf("image error\n");
	else if (error == 6)
		printf("pars color error\n");
	else if (error == 7)
		printf("thread error\n");
	if (ptr->screen.ptr)
		mlx_destroy_image(ptr->mlx.ptr, ptr->screen.ptr);
	// pthread_exit(NULL);
	ft_lstclear(&ptr->malloc_lst, free);
	ft_lstclear_mlx(&ptr->mlx_lst, mlx_destroy_image, ptr);
	free(ptr);
	exit(0);
}

int		ft_quit_x(t_ptr *ptr)
{
	ft_close(ptr, 0);
	return (0);
}
