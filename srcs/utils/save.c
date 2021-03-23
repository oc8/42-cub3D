/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odroz-ba <odroz-ba@student.42lyon.f>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 17:55:40 by odroz-ba          #+#    #+#             */
/*   Updated: 2021/03/23 16:16:41 by odroz-ba         ###   ########lyon.fr   */
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

static unsigned char	*ft_create_bitmap_info_header(t_cub *ptr)
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
	info_header[4] = (unsigned char)(ptr->screen.w >> 0);
	info_header[5] = (unsigned char)(ptr->screen.w >> 8);
	info_header[6] = (unsigned char)(ptr->screen.w >> 16);
	info_header[7] = (unsigned char)(ptr->screen.w >> 24);
	info_header[8] = (unsigned char)(ptr->screen.h >> 0);
	info_header[9] = (unsigned char)(ptr->screen.h >> 8);
	info_header[10] = (unsigned char)(ptr->screen.h >> 16);
	info_header[11] = (unsigned char)(ptr->screen.h >> 24);
	info_header[12] = (unsigned char)(1);
	info_header[14] = (unsigned char)(ptr->screen.bpp);
	return (info_header);
}

void					ft_write_img(int fd, t_cub *ptr)
{
	int	x;
	int	y;

	ft_before_calc(ptr);
	ft_threads(ptr);
	ft_create_plan_sprite(ptr);
	ft_threads(ptr);
	y = -1;
	while (++y < ptr->screen.h)
	{
		x = -1;
		while (++x < ptr->screen.w)
			write(fd, &ptr->screen.pixels[(ptr->screen.h - 1 - y) * \
				(ptr->screen.s_l / 4) + x], 4);
	}
}

void					ft_save_bmp(const char *filename, t_cub *ptr)
{
	int	fd;
	int	img_size;
	int	file_size;

	img_size = ptr->screen.w * ptr->screen.h * 4;
	file_size = img_size + (40 + 14);
	fd = open(filename, O_RDONLY | O_CREAT, S_IRWXU);
	if (fd < 0)
		ft_close(ptr, 1, "open 1 failed\n");
	close(fd);
	fd = open(filename, O_RDWR);
	if (fd < 0)
		ft_close(ptr, 1, "open 2 failed\n");
	write(fd, ft_create_bitmap_file_header(file_size), 14);
	write(fd, ft_create_bitmap_info_header(ptr), 40);
	ft_write_img(fd, ptr);
	close(fd);
	ft_close(ptr, 0, "\033[33msave.bmp generated !");
}
