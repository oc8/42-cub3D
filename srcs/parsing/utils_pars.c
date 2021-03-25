/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pars.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odroz-ba <odroz-ba@student.42lyon.f>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 13:34:01 by odroz-ba          #+#    #+#             */
/*   Updated: 2021/03/25 19:36:31 by odroz-ba         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		ft_atoi_nbr(t_cub *cub, char *line, unsigned int *i)
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
		ft_close(cub, 1, "invalid resolution");
	return (rs);
}

char	*ft_copy_str(t_cub *cub, char *line, unsigned int *i)
{
	char	*rs;
	int		j;
	int		k;

	if (line[*i + 2] != ' ' && line[*i + 2] != '\t')
		ft_close(cub, 1, "extra character");
	*i = ft_skip_spaces(line, *i + 2);
	k = *i;
	j = 0;
	while (line[k] && line[k] != ' ' && line[k] != '\t')
	{
		j++;
		k++;
	}
	if (!j)
		ft_close(cub, 1, "void path");
	rs = ft_calloc_lst(cub, j + 1, sizeof(char));
	j = -1;
	while (line[*i] && line[*i] != ' ' && line[*i] != '\t')
	{
		rs[++j] = line[*i];
		*i += 1;
	}
	rs[++j] = '\0';
	return (rs);
}

int		ft_atoi_color_util(t_cub *cub, char *line, unsigned int *i, int flag)
{
	int		rs;

	while (line[*i] && (line[*i] == ' ' || line[*i] == '\t' || line[*i] == ','))
	{
		if (line[*i] == ',')
			flag++;
		*i += 1;
	}
	if (flag > 1)
		ft_close(cub, 1, "too many ','");
	flag = 0;
	rs = 0;
	while (line[*i] && line[*i] >= '0' && line[*i] <= '9')
	{
		rs = rs * 10 + line[*i] - '0';
		*i += 1;
		flag++;
	}
	if (rs < 0 || rs > 255 || !flag)
		ft_close(cub, 1, "color invalid");
	return (rs);
}

int		ft_atoi_color(t_cub *cub, char *line, unsigned int *i)
{
	int		r;
	int		g;
	int		b;

	r = ft_atoi_color_util(cub, line, i, 1);
	g = ft_atoi_color_util(cub, line, i, 0);
	b = ft_atoi_color_util(cub, line, i, 0);
	return (create_trgb(1, r, g, b));
}
