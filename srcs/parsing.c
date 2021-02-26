/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odroz-ba <odroz-ba@student.42lyon.f>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 14:56:20 by odroz-ba          #+#    #+#             */
/*   Updated: 2021/02/26 15:38:30 by odroz-ba         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

static int	ft_atoi_cub(char *line, int *i, t_ptr *ptr)
{
	int		rs;

	(void)ptr;
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
	rs = ft_check_calloc(ptr, j, sizeof(char));
	j = -1;
	while (line[*i] && line[*i] != ' ' && line[*i] != '\t')
	{
		rs[++j] = line[*i];
		*i += 1;
	}
	rs[++j] = '\0';
	return (rs);
}

static int	ft_parsing_criteria(t_ptr *ptr, char *line)
{
	int		i;

	i = ft_skip_spaces(line, 0);
	if (!line[i])
		return (0);
	if (line[i] == '1' || line[i] == '0' || line[i] == '2')
		return (1);
	if (line[i] == '#')
		return (0);
	else if (line[i] == 'R')
	{
		if (ptr->epars & e_R)
			ft_close(ptr, 3);
		i++;
		if (line[i] != ' ' && line[i] != '\t')
			ft_close(ptr, 3);
		ptr->mlx.width = ft_atoi_cub(line, &i, ptr);
		ptr->mlx.height = ft_atoi_cub(line, &i, ptr);
		ptr->epars |= e_R;
	}
	else if (line[i] == 'N' && line[i + 1] == 'O')
	{
		if (ptr->epars & e_NO)
			ft_close(ptr, 3);
		ptr->pars->path_no = ft_copy_str(ptr, line, &i);
		ptr->emalloc |= e_NO_m;
		ptr->epars |= e_NO;
	}
	else if (line[i] == 'S' && line[i + 1] == 'O')
	{
		if (ptr->epars & e_SO)
			ft_close(ptr, 3);
		ptr->pars->path_so = ft_copy_str(ptr, line, &i);
		ptr->emalloc |= e_SO_m;
		ptr->epars |= e_SO;
	}
	else if (line[i] == 'W' && line[i + 1] == 'E')
	{
		if (ptr->epars & e_WE)
			ft_close(ptr, 3);
		ptr->pars->path_we = ft_copy_str(ptr, line, &i);
		ptr->emalloc |= e_WE_m;
		ptr->epars |= e_WE;
	}
	else if (line[i] == 'E' && line[i + 1] == 'A')
	{
		if (ptr->epars & e_EA)
			ft_close(ptr, 3);
		ptr->pars->path_ea = ft_copy_str(ptr, line, &i);
		ptr->emalloc |= e_EA_m;
		ptr->epars |= e_EA;
	}
	else if (line[i] == 'S')
	{
		if (ptr->epars & e_S)
			ft_close(ptr, 3);
		i--;
		ptr->pars->path_sprite = ft_copy_str(ptr, line, &i);
		ptr->emalloc |= e_S_m;
		ptr->epars |= e_S;
	}
	else if (line[i] == 'F')
	{
		if (ptr->epars & e_F)
			ft_close(ptr, 3);
		i++;
		if (line[i] != ' ' && line[i] != '\t')
			ft_close(ptr, 3);
		ptr->pars->col_floor = 0;////////////////////////////////////
		ptr->epars |= e_F;
		return (0);//
	}
	else if (line[i] == 'C')
	{
		if (ptr->epars & e_C)
			ft_close(ptr, 3);
		i++;
		if (line[i] != ' ' && line[i] != '\t')
			ft_close(ptr, 3);
		ptr->pars->col_sky = 0;////////////////////////////////////
		ptr->epars |= e_C;
		return (0);//
	}
	i = ft_skip_spaces(line, i);
	if (line[i])
		ft_close(ptr, 3);
	return (0);
}

int		ft_parsing(char *path, t_ptr *ptr)
{
	int		fd;
	char	*line;
	int		i;
	int		vr;
	char	flag;
	t_i		first_pos;

	flag = 1;
	if (ft_malloc_map(ptr, path) == -1)
		return (-1);
	fd = open(path, O_RDONLY);
	i = 0;
	vr = 1;
	while (vr)
	{
		vr = get_next_line(fd, &line);
		if (vr == -1)
			ft_close(ptr, 2);
		if (flag && ft_parsing_criteria(ptr, line))
				flag = 0;
		if (!flag) 
			ft_parsing_map(ptr, line, i++, &first_pos);
	}

	printf("\n");
	i = -1; //////
	while (++i < ptr->pars->nbr_map.y) //////
	{
		int j = -1;
		while (++j < ptr->pars->nbr_map.x)
			printf("%c", ptr->pars->map[i][j]); //////
		printf("\n");
	}
	printf("\n");

	if (ptr->epars != 511 || ft_check_map(ptr, ptr->pars->map, first_pos.x, first_pos.y))
		ft_close(ptr, 3);
	ft_malloc_sprite(ptr);
	ft_create_plan(ptr);
	return (0);
}
