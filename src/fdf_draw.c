/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_draw.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jechoque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 15:15:10 by jechoque          #+#    #+#             */
/*   Updated: 2017/11/29 13:56:09 by jechoque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../include/fdf.h"

static void		ft_get_coord(int *tab, t_point *p1, t_point *p2, t_env *e)
{
	tab[0] = p1->x * e->zoom + e->adx;
	tab[1] = (p1->y - (p1->z / (e->z_max / e->ampl))) * e->zoom + e->ady;
	tab[2] = p2->x * e->zoom + e->adx;
	tab[3] = (p2->y - (p2->z / (e->z_max / e->ampl))) * e->zoom + e->ady;
	tab[4] = tab[2] - tab[0];
	tab[5] = tab[3] - tab[1];
}

static t_algo	ft_get_params(int *tab, int dif)
{
	t_algo	par;

	if (dif)
	{
		par.crd1 = tab[0];
		par.crd2 = tab[1];
		par.d1 = abs(tab[4]);
		par.d2 = abs(tab[5]);
		par.inc1 = (tab[4] > 0) ? 1 : -1;
		par.inc2 = (tab[5] > 0) ? 1 : -1;
	}
	else
	{
		par.crd1 = tab[1];
		par.crd2 = tab[0];
		par.d1 = abs(tab[5]);
		par.d2 = abs(tab[4]);
		par.inc1 = (tab[5] > 0) ? 1 : -1;
		par.inc2 = (tab[4] > 0) ? 1 : -1;
	}
	return (par);
}

static void		line_put(t_env *e, t_point *p1, t_point *p2)
{
	t_algo	p;
	int		tab[6];
	int		cumul;
	int		i;

	i = 0;
	ft_get_coord(tab, p1, p2, e);
	p = ft_get_params(tab, (abs(tab[4]) > abs(tab[5])));
	mlx_pixel_put(e->mlx, e->win, tab[0], tab[1] / 1.7, p1->color);
	cumul = p.d1 / 2;
	while (++i <= p.d1)
	{
		p.crd1 += p.inc1;
		cumul += p.d2;
		if (cumul >= p.d1)
		{
			cumul -= p.d1;
			p.crd2 += p.inc2;
		}
		(abs(tab[4]) > abs(tab[5]) ?
		mlx_pixel_put(e->mlx, e->win, p.crd1, p.crd2 / 1.7, ft_zcmp(p1, p2)) :
		mlx_pixel_put(e->mlx, e->win, p.crd2, p.crd1 / 1.7, ft_zcmp(p1, p2)));
	}
}

static t_point	*ft_nextline(int x_max, t_list *map)
{
	int			i;

	i = 0;
	while (i < x_max - 1 && map->next)
	{
		map = map->next;
		i++;
	}
	return (map->content);
}

void			ft_draw(t_env *e)
{
	t_list		*map;
	t_point		*point1;
	t_point		*point2;
	int			tab[6];

	ft_put_menu(e);
	map = e->map;
	if ((point1 = map->content) && !map->next)
	{
		ft_get_coord(tab, point1, point1, e);
		mlx_pixel_put(e->mlx, e->win, tab[0], tab[1], point1->color);
	}
	while (map->next)
	{
		map = map->next;
		point2 = map->content;
		if (point1->index == point2->index)
			line_put(e, point1, point2);
		if (point1->index < e->y_max)
		{
			point2 = ft_nextline(e->x_max, map);
			line_put(e, point1, point2);
		}
		point1 = map->content;
	}
}
