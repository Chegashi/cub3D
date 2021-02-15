/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochegri <mochegri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 23:25:25 by abort             #+#    #+#             */
/*   Updated: 2021/02/15 17:01:04 by mochegri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "cub3d.h"

double	ft_dst_2pnt(t_point p1, t_point p2)
{
	return (sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y)
				* (p1.y - p2.y)));
}

double	ft_min(double x1, double x2)
{
	return (x1 < x2) ? x1 : x2;
}

void	ft_normilised(double *angle)
{
	if (*angle < 0)
		*angle += 2 * PI;
	*angle = (double)fmod(*angle, 2 * PI);
}

double	ft_max(double x1, double x2)
{
	return ((x1 > x2) ? x1 : x2);
}

t_point	ft_translate_point(t_point p, double x, double y)
{
	p.x += x;
	p.y += y;
	return (p);
}

double	deg_to_rad(double x1)
{
	return (x1 * PI / 180);
}

double	rad_to_deg(double x1)
{
	return (x1 * 180 / PI);
}

double	ft_sprite_angl(double y, double x)
{
	double	angle;

	angle = g_game->player->rotationangle -
	atan2f(y - g_game->plyr.y, x - g_game->plyr.x);
	while (angle < -1 * PI)
		angle += (2 * PI);
	while (angle >  PI)
		angle -= (2 * PI);
	return (fabs(angle));
}