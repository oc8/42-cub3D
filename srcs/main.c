/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odroz-ba <odroz-ba@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 14:31:48 by odroz-ba          #+#    #+#             */
/*   Updated: 2021/04/01 13:38:17 by odroz-ba         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
**	steps :
**	- parsing
**	- create rayon for screen
**	- calculates distance
**	- search nearest
**	- search color on texture
*/

static int	ft_error_arg(int nbr)
{
	printf("Error\n");
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

int			ft_check_args(int argc, char *argv[], char *flag_save)
{
	int		i;
	int		j;
	char	*str;

	*flag_save = 0;
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
		*flag_save = 1;
	return (0);
}

int			main(int argc, char *argv[])
{
	t_cub	*cub;
	char	flag_save;

	flag_save = 0;
	if (!(cub = ft_calloc(1, sizeof(t_cub))))
		return (-1);
	if (ft_check_args(argc, argv, &flag_save))
		return (1);
	if (ft_init_struct(cub) == -1)
		return (-1);
	ft_parsing(argv[1], cub);
	ft_mlx_init(cub);
	ft_ray_screen(cub);
	if (flag_save)
		ft_save_bmp("save.bmp", cub);
	ft_cmd("afplay sounds/snk.mp3 &");
	ft_edit_img(cub);
	mlx_loop_hook(cub->mlx.ptr, ft_loop, cub);
	mlx_loop(cub->mlx.ptr);
	return (0);
}
