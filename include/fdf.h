/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jechoque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 11:21:26 by jechoque          #+#    #+#             */
/*   Updated: 2017/11/29 13:58:02 by jechoque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include "../libft/libft.h"
# include <mlx.h>

typedef struct		s_point
{
	int		x;
	int		y;
	int		z;
	int		index;
	int		color;
}					t_point;

typedef struct		s_algo
{
	int		crd1;
	int		crd2;
	int		inc1;
	int		inc2;
	int		d1;
	int		d2;
}					t_algo;

typedef struct		s_env
{
	void	*mlx;
	void	*win;
	int		zoom;
	int		x_max;
	int		y_max;
	int		z_max;
	float	ampl;
	t_list	*map;
	int		adx;
	int		ady;
}					t_env;

# define W_SIZE_X 1800
# define W_SIZE_Y 1200

# define KEYCODE_LEFT 123
# define KEYCODE_RIGHT 124
# define KEYCODE_DOWN 125
# define KEYCODE_UP 126

# define MOUSE_LEFT 1

# define KEYCODE_ONE 18
# define KEYCODE_TWO 19

# define KEYCODE_MINUS 78
# define KEYCODE_PLUS 69

# define KEYCODE_ESC 53

int					ft_zcmp(t_point *point1, t_point *point2);
int					ft_create_map(char **av, t_env *e);
void				ft_put_menu(t_env *e);
void				ft_draw(t_env *e);
int					ft_mouse(int button, int x, int y, void *param);
int					ft_keycode(int keycode, void *param);
void				ft_error(int error);

#endif
