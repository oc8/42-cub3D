/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odroz-ba <odroz-ba@student.42lyon.f>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 11:13:27 by odroz-ba          #+#    #+#             */
/*   Updated: 2021/03/01 14:01:19 by odroz-ba         ###   ########lyon.fr   */
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
	// if (ptr->malloc)
	// {
	// 	ft_lstiter(ptr->malloc, free);
	// }
	ft_lstclear(&ptr->malloc, free);
	free(ptr);
	exit(0);
}

int		ft_quit_X(t_ptr *ptr)
{
	ft_close(ptr, 0);
	return (0);
}