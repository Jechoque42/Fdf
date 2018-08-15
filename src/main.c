/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jechoque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 14:34:55 by jechoque          #+#    #+#             */
/*   Updated: 2017/11/29 13:04:35 by jechoque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../include/fdf.h"

int					main(int argc, char **argv)
{
	t_env			*e;

	if (argc != 2)
		ft_error(2);
	if ((e = (t_env *)malloc(sizeof(t_env))))
	{
		e->x_max = 0;
		if (ft_create_map(argv, e))
		{
			e->mlx = mlx_init();
			e->win = mlx_new_window(e->mlx, W_SIZE_X, W_SIZE_Y, "42 FDF");
			e->zoom = 10;
			e->ampl = 1.5;
			e->ady = (W_SIZE_Y / 3);
			e->adx = (W_SIZE_X / 2);
			ft_put_menu(e);
			ft_draw(e);
			mlx_key_hook(e->win, ft_keycode, e);
			mlx_mouse_hook(e->win, ft_mouse, e);
			mlx_loop(e->mlx);
		}
	}
	ft_error(1);
	return (0);
}
