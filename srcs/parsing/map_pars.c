/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_pars.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odroz-ba <odroz-ba@student.42lyon.f>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 14:56:22 by odroz-ba          #+#    #+#             */
/*   Updated: 2021/03/29 17:44:12 by odroz-ba         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	ft_first_pos(t_cub *cub, char c, int i, int j)
{
	if (cub->epars & e_FIRST_DIR)
		ft_close(cub, 1, "too many player pos");
	cub->epars |= e_FIRST_DIR;
	if (c == 'N')
		cub->player.agl_hor = 0;
	else if (c == 'S')
		cub->player.agl_hor = M_PI_2 * 2;
	else if (c == 'E')
		cub->player.agl_hor = M_PI_2;
	else if (c == 'W')
		cub->player.agl_hor = M_PI_2 * 3;
	cub->player.agl_vrt = 0;
	cub->player.pos.x = i + 0.5;
	cub->player.pos.y = j + 0.5;
	cub->player.pos.z = S_P;
	cub->pars->map[j][i] = '0';
}

static void	ft_check_c(t_cub *cub, char c, unsigned int j, unsigned int i)
{
	if (c == '0' || c == '1' || c == '2' || c == ' ')
		cub->pars->map[j][i] = c;
	else if (c == 'N' || c == 'E' || c == 'S' || c == 'W')
		ft_first_pos(cub, c, i, j);
	else if (c == 'F')
	{
		if (cub->epars & e_FINISH)
			ft_close(cub, 1, "too many 'F'");
		cub->epars |= e_FINISH;
		cub->flag_finish = 1;
		cub->pars->finish.x = i;
		cub->pars->finish.y = j;
		cub->pars->map[j][i] = '0';
	}
	else
		ft_close(cub, 1, "extra caracter in the map");
}

void		ft_parsing_map(t_cub *cub, char *line, int j)
{
	unsigned int	i;

	if (line[0] == '#')
		return ;
	i = -1;
	while (line[++i])
		ft_check_c(cub, line[i], j, i);
	while (++i < cub->pars->nbr_map.x)
		cub->pars->map[j][i] = '0';
}
