/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odroz-ba <odroz-ba@student.42lyon.f>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 11:13:27 by odroz-ba          #+#    #+#             */
/*   Updated: 2021/03/22 10:27:50 by odroz-ba         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_close(t_ptr *ptr, int error, const char *str)
{
	if (error)
		printf("\033[31mError\n");
	printf("%s\n", str);
	if (ptr->screen.ptr)
		mlx_destroy_image(ptr->mlx.ptr, ptr->screen.ptr);
	// pthread_exit(NULL);
	ft_lstclear(&ptr->malloc_lst, free);
	ft_lstclear_mlx(&ptr->mlx_lst, mlx_destroy_image, ptr);
	free(ptr->pars);
	free(ptr);
	exit(0);
}

int		ft_quit_x(t_ptr *ptr)
{
	ft_close(ptr, 0, "close");
	return (0);
}
