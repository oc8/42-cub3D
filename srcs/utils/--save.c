/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   --save.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odroz-ba <odroz-ba@student.42lyon.f>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 17:55:40 by odroz-ba          #+#    #+#             */
/*   Updated: 2021/03/17 17:57:42 by odroz-ba         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static unsigned char	*create_bitmap_file_header(int file_size)
{
	static unsigned char	file_header[] = {
		0, 0,
		0, 0, 0, 0,
		0, 0, 0, 0,
		0, 0, 0, 0,
	};
​
	file_header[0] = (unsigned char)('B');
	file_header[1] = (unsigned char)('M');
	file_header[2] = (unsigned char)(file_size);
	file_header[3] = (unsigned char)(file_size >> 8);
	file_header[4] = (unsigned char)(file_size >> 16);
	file_header[5] = (unsigned char)(file_size >> 24);
	file_header[10] = (unsigned char)(14 + 40);
	return (file_header);
}
​
static unsigned char	*create_bitmap_info_header(t_ptr *ptr)
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
​
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
​
void	write_img(int fd, t_pars *p)
{
	int	x;
	int	y;
​
	y = -1;
	while (++y < p->screen.h)
	{
		x = -1;
		while (++x < p->screen.w)
			write(fd, p->screen.img + x + (p->screen.h - y - 1) * p->screen.s_l, 4);
	}
}
​
int	save_bmp(const char *filename, t_ptr *ptr)
{
	int	fd;
	int	img_size;
	int	file_size;
​
	img_size = pars->screen.w * pars->screen.h * 4;
	file_size = img_size + (40 + 14);
	fd = open(filename, O_RDONLY | O_CREAT, S_IRWXU);
	if (fd < 0)
		quit_prog("fct open() save.c 1 failed\n", pars);
	close(fd);
	fd = open(filename, O_RDWR);
	if (fd < 0)
		quit_prog("fct open() save.c 2 failed\n", pars);
	write(fd, create_bitmap_file_header(file_size), 14);
	write(fd, create_bitmap_info_header(pars), 40);
	write_img(fd, pars);
	close(fd);
	ft_putstr_fd("Image generated!!\n", 1);
	return (1);
}
