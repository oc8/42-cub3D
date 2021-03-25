/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odroz-ba <odroz-ba@student.42lyon.f>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 17:55:40 by odroz-ba          #+#    #+#             */
/*   Updated: 2021/03/25 11:33:34 by odroz-ba         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static unsigned char	*ft_create_bitmap_file_header(int file_size)
{
	static unsigned char	file_header[] = {
		0, 0,
		0, 0, 0, 0,
		0, 0, 0, 0,
		0, 0, 0, 0,
	};

	file_header[0] = (unsigned char)('B');
	file_header[1] = (unsigned char)('M');
	file_header[2] = (unsigned char)(file_size);
	file_header[3] = (unsigned char)(file_size >> 8);
	file_header[4] = (unsigned char)(file_size >> 16);
	file_header[5] = (unsigned char)(file_size >> 24);
	file_header[10] = (unsigned char)(14 + 40);
	return (file_header);
}

static unsigned char	*ft_create_bitmap_info_header(t_cub *cub)
{
	static unsigned char	info_header[] = {
		0, 0, 0, 0,
		0, 0, 0, 0,
		0, 0, 0, 0,
		0, 0,
		0, 0,
		0, 0, 0, 0,
		0, 0, 0, 0,
		0, 0, 0, 0,
		0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0,
	};

	info_header[0] = (unsigned char)(40);
	info_header[4] = (unsigned char)(cub->scr.w >> 0);
	info_header[5] = (unsigned char)(cub->scr.w >> 8);
	info_header[6] = (unsigned char)(cub->scr.w >> 16);
	info_header[7] = (unsigned char)(cub->scr.w >> 24);
	info_header[8] = (unsigned char)(cub->scr.h >> 0);
	info_header[9] = (unsigned char)(cub->scr.h >> 8);
	info_header[10] = (unsigned char)(cub->scr.h >> 16);
	info_header[11] = (unsigned char)(cub->scr.h >> 24);
	info_header[12] = (unsigned char)(1);
	info_header[14] = (unsigned char)(cub->scr.bpp);
	return (info_header);
}

void					ft_write_img(int fd, t_cub *cub)
{
	int	x;
	int	y;

	ft_before_calc(cub);
	ft_threads(cub);
	ft_create_plan_sprite(cub);
	ft_threads(cub);
	y = -1;
	while (++y < cub->scr.h)
	{
		x = -1;
		while (++x < cub->scr.w)
			write(fd, &cub->scr.pixels[(cub->scr.h - 1 - y) * \
				(cub->scr.s_l / 4) + x], 4);
	}
}

void					ft_save_bmp(const char *filename, t_cub *cub)
{
	int	fd;
	int	img_size;
	int	file_size;

	img_size = cub->scr.w * cub->scr.h * 4;
	file_size = img_size + (40 + 14);
	fd = open(filename, O_RDONLY | O_CREAT, S_IRWXU);
	if (fd < 0)
		ft_close(cub, 1, "open 1 failed\n");
	close(fd);
	fd = open(filename, O_RDWR);
	if (fd < 0)
		ft_close(cub, 1, "open 2 failed\n");
	write(fd, ft_create_bitmap_file_header(file_size), 14);
	write(fd, ft_create_bitmap_info_header(cub), 40);
	ft_write_img(fd, cub);
	close(fd);
	ft_close(cub, 0, "\033[33msave.bmp generated !");
}
