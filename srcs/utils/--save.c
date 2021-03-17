#include "cub3D.h"

static void	write_int(int fd, int i, int size)
{
	write(fd, &i, size);
}

static void	fill_file_header(int fd, t_ptr *ptr)
{
	int	file_size;

	file_size = ptr->win.x_w * ptr->win.y_w * 4 + 54;
	write(fd, "BM", 2);
	write(fd, &file_size, 4);
	write_int(fd, 0, 4);
	write_int(fd, 54, 4);
}

static void	fill_file_info(int fd, t_ptr *ptr)
{
	int	img_width;
	int	img_height;
	int	bpp;

	img_width = ptr->win.x_w;
	img_height = ptr->win.y_w;
	bpp = ptr->img.bpp;
	write_int(fd, 40, 4);
	write(fd, &img_width, 4);
	write(fd, &img_height, 4);
	write_int(fd, 1, 2);
	write(fd, &bpp, 2);
	write_int(fd, 0, 4);
	write_int(fd, 0, 4);
	write_int(fd, 0, 4);
	write_int(fd, 0, 4);
	write_int(fd, 0, 4);
	write_int(fd, 0, 4);
}

static void	fill_file_body(int fd, t_ptr *ptr)
{
	int	x;
	int	y;
	int color;

	y = ptr->save.w - 1;
	while (y >= 0)
	{
		x = 0;
		while (x < ptr->save.w)
		{
			color = ptr->save.pixels[y * (ptr->save.s_l / 4) + x];
			write(fd, &color, 4);
			x++;
		}
		y--;
	}
}

void			save_image(char *name, t_ptr *ptr)
{
	int		fd;
	int		len;

	len = ptr->save.w * ptr->save.w;
	if (ft_display_image(&ptr, ptr->win, ptr->player, 1) < 0)
		ft_close(ptr, 2);
	fd = open(name, O_CREAT | O_TRUNC | O_RDWR, 0777);
	if (fd == -1)
        ft_close(ptr, 2);
	fill_file_header(fd, ptr);
	fill_file_info(fd, ptr);
	fill_file_body(fd, ptr);
	free_all_ptr(&ptr);
}