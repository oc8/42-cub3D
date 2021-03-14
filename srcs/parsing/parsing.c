/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odroz-ba <odroz-ba@student.42lyon.f>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 14:56:20 by odroz-ba          #+#    #+#             */
/*   Updated: 2021/03/14 18:39:58 by odroz-ba         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	ft_atoi_nbr(t_ptr *ptr, char *line, int *i)
{
	int		rs;

	while (line[*i] && (line[*i] == ' ' || line[*i] == '\t'))
		*i += 1;
	rs = 0;
	while (line[*i] && line[*i] >= '0' && line[*i] <= '9')
	{
		rs = rs * 10 + line[*i] - '0';
		*i += 1;
	}
	if (!rs)
		ft_close(ptr, 3);
	return (rs);
}

static int	ft_skip_spaces(char *line, int i)
{
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	return (i);
}

static char	*ft_copy_str(t_ptr *ptr, char *line, int *i)
{
	char	*rs;
	int		j;
	int		k;

	if (line[*i + 2] != ' ' && line[*i + 2] != '\t')
		ft_close(ptr, 3);
	*i = ft_skip_spaces(line, *i + 2);
	k = *i;
	j = 0;
	while (line[k] && line[k] != ' ' && line[k] != '\t')
	{
		j++;
		k++;
	}
	if (!j)
		ft_close(ptr, 3);
	rs = ft_calloc_lst(ptr, j + 1, sizeof(char));
	j = -1;
	while (line[*i] && line[*i] != ' ' && line[*i] != '\t')
	{
		rs[++j] = line[*i];
		*i += 1;
	}
	rs[++j] = '\0';
	return (rs);
}

static int	ft_atoi_color_util(t_ptr *ptr, char *line, int *i, int flag)
{
	int		rs;

	while (line[*i] && (line[*i] == ' ' || line[*i] == '\t' || line[*i] == ','))
	{
		if (line[*i] == ',')
			flag++;
		*i += 1;
	}
	if (flag > 1)
		ft_close(ptr, 6);
	flag = 0;
	rs = 0;
	while (line[*i] && line[*i] >= '0' && line[*i] <= '9')
	{
		rs = rs * 10 + line[*i] - '0';
		*i += 1;
		flag++;
	}
	if (rs < 0 || rs > 255 || !flag)
		ft_close(ptr, 6);
	return (rs);
}

static int	ft_atoi_color(t_ptr *ptr, char *line, int *i)
{
	int		r;
	int		g;
	int		b;

	r = ft_atoi_color_util(ptr, line, i, 1);
	g = ft_atoi_color_util(ptr, line, i, 0);
	b = ft_atoi_color_util(ptr, line, i, 0);
	return (create_trgb(1, r, g, b));
}

void	ft_pars_resolution(t_ptr *ptr, t_line line, int e_res)
{
	int		x;
	int		y;
	int		*i;

	i = line.i_ptr;
	if (ptr->epars & e_res)
		ft_close(ptr, 3);
	*i += 1;
	if (line.ptr[*i] != ' ' && line.ptr[*i] != '\t')
		ft_close(ptr, 3);
	ptr->mlx.width = ft_atoi_nbr(ptr, line.ptr, i);
	ptr->mlx.height = ft_atoi_nbr(ptr, line.ptr, i);
	mlx_get_screen_size(ptr->mlx.ptr, &x, &y);
	if (ptr->mlx.width > x)
		ptr->mlx.width = x;
	if (ptr->mlx.height > y)
		ptr->mlx.height = y;
	ptr->epars |= e_res;
}

void	ft_pars_path(t_ptr *ptr, t_line line, char **path, int e_wall)
{
	if (ptr->epars & e_wall)
		ft_close(ptr, 3);
	*path = ft_copy_str(ptr, line.ptr, line.i_ptr);
	ptr->epars |= e_wall;
}

static int	ft_parsing_criteria(t_ptr *ptr, t_line line)
{
	int		i;

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
	else if (line.ptr[i] == 'N' && line.ptr[i + 1] == 'O')
		ft_pars_path(ptr, line, &ptr->pars->path_no, e_NO);
	else if (line.ptr[i] == 'S' && line.ptr[i + 1] == 'O')
		ft_pars_path(ptr, line, &ptr->pars->path_so, e_SO);
	else if (line.ptr[i] == 'W' && line.ptr[i + 1] == 'E')
		ft_pars_path(ptr, line, &ptr->pars->path_we, e_WE);
	else if (line.ptr[i] == 'E' && line.ptr[i + 1] == 'A')
		ft_pars_path(ptr, line, &ptr->pars->path_ea, e_EA);
	else if (line.ptr[i] == 'S')
	{
		if (ptr->epars & e_S)
			ft_close(ptr, 3);
		i--;
		ptr->pars->path_sprite = ft_copy_str(ptr, line.ptr, &i);
		ptr->epars |= e_S;
	}
	else if (line.ptr[i] == 'F')
	{
		if (ptr->epars & e_F)
			ft_close(ptr, 3);
		i++;
		if (line.ptr[i] != ' ' && line.ptr[i] != '\t')
			ft_close(ptr, 3);
		ptr->pars->col_floor = ft_atoi_color(ptr, line.ptr, &i);
		ptr->epars |= e_F;
	}
	else if (line.ptr[i] == 'C')
	{
		if (ptr->epars & e_C)
			ft_close(ptr, 3);
		i++;
		if (line.ptr[i] != ' ' && line.ptr[i] != '\t')
			ft_close(ptr, 3);
		ptr->pars->col_sky = ft_atoi_color(ptr, line.ptr, &i);
		ptr->epars |= e_C;
	}
	i = ft_skip_spaces(line.ptr, i);
	if (line.ptr[i])
		ft_close(ptr, 3);
	return (0);
}

int		ft_parsing(char *path, t_ptr *ptr)
{
	int		fd;
	t_line	line;
	int		vr;
	char	flag;
	t_i		first_pos;

	flag = 1;
	if (ft_malloc_map(ptr, path) == -1)
		return (-1);
	fd = open(path, O_RDONLY);
	line.i = 0;
	vr = 1;
	while (vr)
	{
		vr = get_next_line(fd, &line.ptr);
		if (vr == -1)
		{
			free(line.ptr);
			ft_close(ptr, 2);
		}
		if (flag && ft_parsing_criteria(ptr, line))
				flag = 0;
		if (!flag)
			ft_parsing_map(ptr, line.ptr, line.i++, &first_pos);
		free(line.ptr);
	}

	printf("\n");
	line.i = -1; //////
	while (++line.i < ptr->pars->nbr_map.y) //////
	{
		int j = -1;
		while (++j < ptr->pars->nbr_map.x)
			printf("%c", ptr->pars->map[line.i][j]); //////
		printf("\n");
	}
	printf("\n");

	if (ptr->epars != 511 || ft_check_map(ptr, ptr->pars->map, first_pos.x, first_pos.y))
		ft_close(ptr, 3);
	ft_malloc_sprite(ptr);
	ft_pos_sprite(ptr);
	ft_create_plan(ptr);
	return (0);
}
