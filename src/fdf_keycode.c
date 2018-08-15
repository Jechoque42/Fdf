/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_keycode.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jechoque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 10:57:46 by jechoque          #+#    #+#             */
/*   Updated: 2017/11/29 13:57:05 by jechoque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "../include/fdf.h"

void			ft_put_menu(t_env *e)
{
	mlx_string_put(e->mlx, e->win, 5, 5, 0x00FFFFFF, "##################");
	mlx_string_put(e->mlx, e->win, 5, 30, 0x00FFFFFF, "Cam:");
	mlx_string_put(e->mlx, e->win, 5, 55, 0x00FFFFFF, "^  v : UP, DOWN");
	mlx_string_put(e->mlx, e->win, 5, 80, 0x00FFFFFF, "<  > : LEFT, RIGHT");
	mlx_string_put(e->mlx, e->win, 5, 105, 0x00FFFFFF, "Zoom:");
	mlx_string_put(e->mlx, e->win, 5, 130, 0x00FFFFFF, "+ : ZOOM +");
	mlx_string_put(e->mlx, e->win, 5, 155, 0x00FFFFFF, "- : ZOOM -");
	mlx_string_put(e->mlx, e->win, 5, 180, 0x00FFFFFF, "Amplification:");
	mlx_string_put(e->mlx, e->win, 5, 205, 0x00FFFFFF, "1 : MORE");
	mlx_string_put(e->mlx, e->win, 5, 230, 0x00FFFFFF, "2 : LESS");
	mlx_string_put(e->mlx, e->win, 5, 255, 0x00FFFFFF, "##################");
}

void			ft_delmap(t_list *map)
{
	t_list	*tmp;
	t_point	*point;

	while (map)
	{
		tmp = map->next;
		point = map->content;
		free(point);
		map->next = NULL;
		free(map);
		map = tmp;
	}
	tmp = NULL;
}

int				ft_mouse(int button, int x, int y, void *param)
{
	t_env	*e;

	e = param;
	if (button == MOUSE_LEFT)
	{
		e->adx = x;
		e->ady = y;
		mlx_clear_window(e->mlx, e->win);
		ft_draw(e);
	}
	return (button);
}

int				ft_keycode(int keycode, void *param)
{
	t_list	*map;
	t_env	*e;

	if ((e = param) && keycode == KEYCODE_ESC)
	{
		map = e->map;
		mlx_destroy_window(e->mlx, e->win);
		ft_delmap(map);
		e = NULL;
		exit(0);
	}
	if (keycode == KEYCODE_ONE || keycode == KEYCODE_TWO)
		e->ampl += (keycode == KEYCODE_ONE ? 0.5 : -0.5);
	else if (keycode == KEYCODE_LEFT || keycode == KEYCODE_RIGHT)
		e->adx += (keycode == KEYCODE_LEFT ? e->zoom : -e->zoom);
	else if (keycode == KEYCODE_UP || keycode == KEYCODE_DOWN)
		e->ady += (keycode == KEYCODE_UP ? e->zoom : -e->zoom);
	else if (keycode == KEYCODE_PLUS)
		e->zoom += 2;
	else if (keycode == KEYCODE_MINUS)
		if (e->zoom > 2)
			e->zoom -= 2;
	mlx_clear_window(e->mlx, e->win);
	ft_draw(e);
	return (keycode);
}
