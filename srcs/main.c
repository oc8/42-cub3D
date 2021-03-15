/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odroz-ba <odroz-ba@student.42lyon.f>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 14:31:48 by odroz-ba          #+#    #+#             */
/*   Updated: 2021/03/15 13:50:45 by odroz-ba         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int		ft_init_struct(t_ptr *ptr)
{
	ptr->epars = 0;
	ptr->player.speed = 0.5;
	ptr->pars->nbr_sprite = 0;
	ptr->time.tv_sec = 0;
	ptr->time.tv_usec = 0;
	ptr->last_second = ft_time_now();
	return (0);
}

static int	ft_error_arg(int nbr)
{
	if (nbr == 1)
		printf("nbr arg error\n");
	else if (nbr == 2)
		printf("arg error\n");
	else if (nbr == 3)
		printf("\".cub\" error\n");
	else if (nbr == 4)
		printf("\"--save\" error\n");
	return (1);
}

int		ft_check_args(int argc, char *argv[])
{
	int		i;
	int		j;
	char	*str;

	if (argc != 2 && argc != 3)
		return (ft_error_arg(1));
	i = ft_strlen(argv[1]);
	str = ".cub";
	if (i < 4)
		return (ft_error_arg(2));
	j = 4;
	while (j)
		if (argv[1][--i] != str[--j])
			return (ft_error_arg(3));
	if (argc == 3 && ft_strncmp(argv[2], "--save", 7))
		return (ft_error_arg(4));
	if (argc == 3)
		;
	return (0);
}

void	ft_ray_screen(t_ptr *ptr)
{
	float	fov;
	float	fov_x;
	float	fov_y;
	int		x;
	int		y;

	fov = 100 * M_PI / 180;
	fov_x = 2 * tan(fov / 2);
	fov_y = 2 * tan(fov * ptr->mlx.height / ptr->mlx.width * 0.5);
	ptr->player.dir = ft_calloc_lst(ptr, ptr->mlx.height * ptr->mlx.width, \
			sizeof(t_c));
	y = -1;
	while (++y < ptr->mlx.height)
	{
		x = -1;
		while (++x < ptr->mlx.width)
		{
			ptr->player.dir[y * ptr->mlx.width + x].x = fov_x / ptr->mlx.width * \
				(x - ptr->mlx.width * 0.5);
			ptr->player.dir[y * ptr->mlx.width + x].y = -1;
			ptr->player.dir[y * ptr->mlx.width + x].z = -fov_y / ptr->mlx.height * \
				(y - ptr->mlx.height * 0.5);
		}
	}
}

int		main(int argc, char *argv[])
{
	t_ptr	*ptr;

	if (ft_check_args(argc, argv))
		return (1);
	if (!(ptr = ft_calloc(1, sizeof(t_ptr))))
		return (-1);
	if (!(ptr->pars = ft_calloc(1, sizeof(t_pars))))
	{
		free(ptr);
		printf("malloc error\n");
		return (-1);
	}
	if (ft_init_struct(ptr) == -1)
		return (-1);
	ft_parsing(argv[1], ptr);
	ft_mlx_init(ptr);
	ft_ray_screen(ptr);
	ft_edit_img(ptr);
	mlx_loop_hook(ptr->mlx.ptr, ft_loop, ptr);
	mlx_loop(ptr->mlx.ptr);
	return (0);
}
