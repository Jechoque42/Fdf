/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_parcer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jechoque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/21 13:11:29 by jechoque          #+#    #+#             */
/*   Updated: 2017/11/22 14:39:55 by jechoque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "../include/fdf.h"

int					ft_zcmp(t_point *point1, t_point *point2)
{
	if (point1->z > point2->z)
		return (point1->color);
	return (point2->color);
}

static void			ft_getcolor(t_point *point)
{
	if (point->z <= 0 && point->z > -70)
		point->color = 0x0000FF;
	if (point->z <= -70 && point->z > -450)
		point->color = 0x0000CC;
	if (point->z <= -450)
		point->color = 0x000099;
	if (point->z > 0 && point->z <= 40)
		point->color = 0x669900;
	if (point->z > 40 && point->z <= 110)
		point->color = 0x666600;
	if (point->z > 110 && point->z <= 160)
		point->color = 0x663300;
	if (point->z > 160 && point->z <= 290)
		point->color = 0x660000;
	if (point->z > 290)
		point->color = 0x00FFFFFF;
}

static t_list		*ft_gen_point(char *z, int y, int x_max, t_env *e)
{
	t_list			*elem;
	t_point			*point;

	if (x_max == 0 && y == 1)
		e->z_max = 1;
	if (!(point = (t_point *)malloc(sizeof(t_point))))
		ft_error(1);
	point->z = ft_getnbr(z);
	point->x = x_max + 1 - y;
	point->index = y;
	point->y = (y + x_max + 1);
	ft_getcolor(point);
	if (e->z_max < point->z)
		e->z_max = point->z;
	elem = ft_lstnew(point, sizeof(t_point));
	free(point);
	point = NULL;
	return (elem);
}

static t_list		*ft_parce_line(char *line, t_env *e, t_list *map)
{
	char			**point;
	int				x_max;

	x_max = 0;
	point = ft_strsplit(line, ' ');
	while (point[x_max] != NULL)
	{
		(map == NULL ?
		ft_lstadd(&map, ft_gen_point(point[x_max], e->y_max, x_max, e)) :
		ft_lstadd_back(&map, ft_gen_point(point[x_max], e->y_max, x_max, e)));
		ft_strdel(&point[x_max]);
		x_max++;
	}
	free(point);
	point = NULL;
	if (e->x_max == 0)
		e->x_max = x_max;
	else if (e->x_max != x_max)
		ft_error(4);
	return (map);
}

int					ft_create_map(char **av, t_env *e)
{
	t_list			*map;
	int				fd;
	char			*line;

	map = NULL;
	e->y_max = 0;
	if (0 > (fd = open(av[1], O_RDONLY)))
		ft_error(3);
	while (get_next_line(fd, &line) == 1 && ++(e->y_max))
	{
		map = ft_parce_line(line, e, map);
		ft_strdel(&line);
	}
	if (map == NULL)
		ft_error(4);
	if (line && *line)
		ft_strdel(&line);
	if (close(fd) < 0)
		ft_error(3);
	e->map = map;
	map = NULL;
	return (1);
}
