/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   criteria.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odroz-ba <odroz-ba@student.42lyon.f>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 18:51:52 by odroz-ba          #+#    #+#             */
/*   Updated: 2021/03/23 18:53:39 by odroz-ba         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		ft_pars_resolution(t_cub *cub, t_line line, int e_res)
{
	int				x;
	int				y;
	unsigned int	*i;

	i = line.i_ptr;
	if (cub->epars & e_res)
		ft_close(cub, 1, "too many criteria 'R'");
	*i += 1;
	if (line.ptr[*i] != ' ' && line.ptr[*i] != '\t')
		ft_close(cub, 1, "extra character");
	cub->screen.w = ft_atoi_nbr(cub, line.ptr, i);
	cub->screen.h = ft_atoi_nbr(cub, line.ptr, i);
	mlx_get_screen_size(cub->mlx.ptr, &x, &y);
	if (cub->screen.w > x)
		cub->screen.w = x;
	if (cub->screen.h > y)
		cub->screen.h = y;
	cub->epars |= e_res;
}

void		ft_pars_path(t_cub *cub, t_line line, char **path, int e_wall)
{
	if (cub->epars & e_wall)
		ft_close(cub, 1, "too many criteria wall");
	*path = ft_copy_str(cub, line.ptr, line.i_ptr);
	cub->epars |= e_wall;
}

static void	ft_criteria_color(t_cub *cub, t_line line, unsigned int *i)
{
	if (line.ptr[*i] == 'F')
	{
		if (cub->epars & e_F)
			ft_close(cub, 1, "too many criteria 'F'");
		*i += 1;
		if (line.ptr[*i] != ' ' && line.ptr[*i] != '\t')
			ft_close(cub, 1, "extra character");
		cub->pars->col_floor = ft_atoi_color(cub, line.ptr, i);
		cub->epars |= e_F;
	}
	else if (line.ptr[*i] == 'C')
	{
		if (cub->epars & e_C)
			ft_close(cub, 1, "too many criteria 'C'");
		*i += 1;
		if (line.ptr[*i] != ' ' && line.ptr[*i] != '\t')
			ft_close(cub, 1, "extra character");
		cub->pars->col_sky = ft_atoi_color(cub, line.ptr, i);
		cub->epars |= e_C;
	}
}

static void	ft_criteria_path_texture(t_cub *cub, t_line line, unsigned int *i)
{
	if (line.ptr[*i] == 'N' && line.ptr[*i + 1] == 'O')
		ft_pars_path(cub, line, &cub->pars->path_no, e_NO);
	else if (line.ptr[*i] == 'S' && line.ptr[*i + 1] == 'O')
		ft_pars_path(cub, line, &cub->pars->path_so, e_SO);
	else if (line.ptr[*i] == 'W' && line.ptr[*i + 1] == 'E')
		ft_pars_path(cub, line, &cub->pars->path_we, e_WE);
	else if (line.ptr[*i] == 'E' && line.ptr[*i + 1] == 'A')
		ft_pars_path(cub, line, &cub->pars->path_ea, e_EA);
	else if (line.ptr[*i] == 'S')
	{
		if (cub->epars & e_S)
			ft_close(cub, 1, "too many criteria 'S'");
		*i -= 1;
		cub->pars->path_sprite = ft_copy_str(cub, line.ptr, i);
		cub->epars |= e_S;
	}
	else
		ft_criteria_color(cub, line, i);
}

int			ft_parsing_criteria(t_cub *cub, t_line line)
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
		ft_pars_resolution(cub, line, e_R);
	else
		ft_criteria_path_texture(cub, line, &i);
	i = ft_skip_spaces(line.ptr, i);
	if (line.ptr[i])
		ft_close(cub, 1, "extra character");
	return (0);
}
