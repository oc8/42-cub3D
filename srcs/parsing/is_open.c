/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_open.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odroz-ba <odroz-ba@student.42lyon.f>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 18:34:49 by odroz-ba          #+#    #+#             */
/*   Updated: 2021/03/29 19:29:44 by odroz-ba         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_open.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odroz-ba <odroz-ba@student.42lyon.f>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 18:34:49 by odroz-ba          #+#    #+#             */
/*   Updated: 2021/03/29 19:18:38 by odroz-ba         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	ft_check_c(t_cub *cub, char **map, int j, int i)
{
	char	c;

	// unsigned int k;
	// printf("\n");
	// k = -1; //////
	// while (++k < cub->pars->nbr_map.y) //////
	// {
	// 	unsigned int l = -1;
	// 	while (++l < cub->pars->nbr_map.x)
	// 	{
	// 		if (!map[k][l])
	// 			printf("O");
	// 		else if (map[k][l] == 2)
	// 			printf("2");
	// 		else
	// 			printf("%c", map[k][l]); //////
	// 	}
	// 	printf("\n");
	// }
	// printf("\n");
	// usleep(500);
	c = map[j][i];
	if (c == '1' || c == 0 || c == 2)
		return (0);
	if (c == '2')
		c = 2;
	else if (c == '0')
		c = 0;
	else
		ft_close(cub, 1, "extra caracter in the map");
	ft_check_map(cub, map, i, j);
	return (1);
}

char		ft_check_map(t_cub *cub, char **map, int i, int j)
{
	if (i - 1 < 0 || i + 1 >= (int)cub->pars->nbr_map.x)
		ft_close(cub, 1, "open map");
	if (j - 1 < 0 || j + 1 >= (int)cub->pars->nbr_map.y)
		ft_close(cub, 1, "open map");
	if (ft_check_c(cub, map, j, i - 1))
		return (1);
	if (ft_check_c(cub, map, j, i + 1))
		return (1);
	if (ft_check_c(cub, map, j - 1, i))
		return (1);
	if (ft_check_c(cub, map, j + 1, i))
		return (1);
	if (ft_check_c(cub, map, j - 1, i - 1))
		return (1);
	if (ft_check_c(cub, map, j + 1, i + 1))
		return (1);
	if (ft_check_c(cub, map, j - 1, i + 1))
		return (1);
	if (ft_check_c(cub, map, j + 1, i - 1))
		return (1);
	return (0);
}

