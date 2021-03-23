/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odroz-ba <odroz-ba@student.42lyon.f>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 14:56:20 by odroz-ba          #+#    #+#             */
/*   Updated: 2021/03/23 16:16:41 by odroz-ba         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		ft_pars_resolution(t_cub *ptr, t_line line, int e_res)
{
	int		x;
	int		y;
	unsigned int	*i;

	i = line.i_ptr;
	if (ptr->epars & e_res)
		ft_close(ptr, 1, "too many criteria 'R'");
	*i += 1;
	if (line.ptr[*i] != ' ' && line.ptr[*i] != '\t')
		ft_close(ptr, 1, "extra character");
	ptr->screen.w = ft_atoi_nbr(ptr, line.ptr, i);
	ptr->screen.h = ft_atoi_nbr(ptr, line.ptr, i);
	mlx_get_screen_size(ptr->mlx.ptr, &x, &y);
	if (ptr->screen.w > x)
		ptr->screen.w = x;
	if (ptr->screen.h > y)
		ptr->screen.h = y;
	ptr->epars |= e_res;
}

void		ft_pars_path(t_cub *ptr, t_line line, char **path, int e_wall)
{
	if (ptr->epars & e_wall)
			ft_close(ptr, 1, "too many criteria wall");
	*path = ft_copy_str(ptr, line.ptr, line.i_ptr);
	ptr->epars |= e_wall;
}

static void	ft_criteria_color(t_cub *ptr, t_line line, unsigned int *i)
{
	if (line.ptr[*i] == 'F')
	{
		if (ptr->epars & e_F)
			ft_close(ptr, 1, "too many criteria 'F'");
		*i += 1;
		if (line.ptr[*i] != ' ' && line.ptr[*i] != '\t')
			ft_close(ptr, 1, "extra character");
		ptr->pars->col_floor = ft_atoi_color(ptr, line.ptr, i);
		ptr->epars |= e_F;
	}
	else if (line.ptr[*i] == 'C')
	{
		if (ptr->epars & e_C)
			ft_close(ptr, 1, "too many criteria 'C'");
		*i += 1;
		if (line.ptr[*i] != ' ' && line.ptr[*i] != '\t')
			ft_close(ptr, 1, "extra character");
		ptr->pars->col_sky = ft_atoi_color(ptr, line.ptr, i);
		ptr->epars |= e_C;
	}
}

static void	ft_criteria_path_texture(t_cub *ptr, t_line line, unsigned int *i)
{
	if (line.ptr[*i] == 'N' && line.ptr[*i + 1] == 'O')
		ft_pars_path(ptr, line, &ptr->pars->path_no, e_NO);
	else if (line.ptr[*i] == 'S' && line.ptr[*i + 1] == 'O')
		ft_pars_path(ptr, line, &ptr->pars->path_so, e_SO);
	else if (line.ptr[*i] == 'W' && line.ptr[*i + 1] == 'E')
		ft_pars_path(ptr, line, &ptr->pars->path_we, e_WE);
	else if (line.ptr[*i] == 'E' && line.ptr[*i + 1] == 'A')
		ft_pars_path(ptr, line, &ptr->pars->path_ea, e_EA);
	else if (line.ptr[*i] == 'S')
	{
		if (ptr->epars & e_S)
			ft_close(ptr, 1, "too many criteria 'S'");
		*i -= 1;
		ptr->pars->path_sprite = ft_copy_str(ptr, line.ptr, i);
		ptr->epars |= e_S;
	}
	else
		ft_criteria_color(ptr, line, i);
}

static int	ft_parsing_criteria(t_cub *ptr, t_line line)
{
	unsigned int	i;

	i = ft_skip_spaces(line.ptr, 0);
	line.i_ptr = &i;
	if (!line.ptr[i])
		return (0);
	if (line.ptr[i] == '1' || line.ptr[i] == '0' || line.ptr[i] == '2')
		return (1);
	if (line.ptr[i] == '#')
		return (0);
	else if (line.ptr[i] == 'R')
		ft_pars_resolution(ptr, line, e_R);
	else
		ft_criteria_path_texture(ptr, line, &i);
	i = ft_skip_spaces(line.ptr, i);
	if (line.ptr[i])
		ft_close(ptr, 1, "extra character");
	return (0);
}

static void	ft_parsing_loop(t_cub *ptr, char *path, t_i *first_pos)
{
	int		fd;
	t_line	line;
	int		vr;
	char	flag;

	flag = 1;
	fd = open(path, O_RDONLY);
	line.i = 0;
	vr = 1;
	while (vr)
	{
		vr = get_next_line(fd, &line.ptr);
		if (vr == -1)
		{
			free(line.ptr);
			ft_close(ptr, 1, "get_next_line() error");
		}
		if (flag && ft_parsing_criteria(ptr, line))
			flag = 0;
		if (!flag)
			ft_parsing_map(ptr, line.ptr, line.i++, first_pos);
		free(line.ptr);
	}
}

int			ft_parsing(char *path, t_cub *ptr)
{
	t_i		first_pos;

	if (ft_malloc_map(ptr, path) == -1)
		return (-1);
	ft_parsing_loop(ptr, path, &first_pos);
	if (ptr->epars != 511 && ptr->epars != 1023)
		ft_close(ptr, 1, "missing criteria");
	if (ft_check_map(ptr, ptr->pars->map, first_pos.x, first_pos.y))
		ft_close(ptr, 1, "open map");
	ft_malloc_sprite(ptr);
	ft_pos_sprite(ptr);
	ft_create_plan(ptr);
	return (0);
}
