/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odroz-ba <odroz-ba@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 11:13:27 by odroz-ba          #+#    #+#             */
/*   Updated: 2021/03/31 20:57:23 by odroz-ba         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_close(t_cub *cub, int error, const char *str)
{
	if (error)
		printf("\033[31mError\n");
	printf("%s\n", str);
	ft_lstclear(&cub->malloc_lst, free);
	ft_lstclear_mlx(&cub->mlx_lst, mlx_destroy_image, cub);
	free(cub->pars);
	free(cub);
	exit(0);
}

int		ft_quit_x(t_cub *cub)
{
	ft_close(cub, 0, "close");
	return (0);
}
