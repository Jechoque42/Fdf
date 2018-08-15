/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jechoque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 14:21:44 by jechoque          #+#    #+#             */
/*   Updated: 2017/11/22 11:56:03 by jechoque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../include/fdf.h"

void		ft_error(int error)
{
	if (error == 1)
		ft_putstr("malloc error\n");
	if (error == 2)
		ft_putstr("usage: fdf source_file\n");
	if (error == 3)
		ft_putstr("file descriptor error\n");
	if (error == 4)
		ft_putstr("not a valid file\n");
	exit(0);
}
