/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochegri <mochegri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/02 09:55:17 by mochegri          #+#    #+#             */
/*   Updated: 2021/02/24 19:29:43 by mochegri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>

t_player		*ft_init_player(t_cub *cub)
{
	t_player	*player;

	player = (t_player*)malloc(sizeof(t_player));
	player->x = (cub->player_position[1]) * g_game->ts + g_game->ts / 2;
	player->y = (cub->player_position[0]) * g_game->ts + g_game->ts / 2;
	if (cub->direction == 'N')
		player->rotationangle = (3 * PI) / 2;
	if (cub->direction == 'E')
		player->rotationangle = 0;
	if (cub->direction == 'S')
		player->rotationangle = PI / 2;
	if (cub->direction == 'W')
		player->rotationangle = PI;
	player->turndirection = 0;
	player->walkdirection = 0;
	player->walkspeed = g_game->ts / 3;
	player->turnspeed = 5 * (PI / 180);
	player->z = 0;
	return (player);
}

int				key_hook(int keycode)
{
	t_player	*p;

	p = (t_player *)malloc(sizeof(t_player));
	*p = *g_game->player;
	p->turndirection = 0;
	ft_key_utils(keycode, p);
	ft_update(p);
	return (0);
}

int				mouse_hook(int button, int x, int y)
{
	if (button == 1)
	{
		g_game->player->x = x;
		g_game->player->y = y;
	}
	return (0);
}

void			ft_render_player(void)
{
	t_point		p1;
	t_point		p2;

	p1.x = g_game->player->x;
	p1.y = g_game->player->y;
	p2.x = (p1.x + cos(g_game->player->rotationangle) * 20 * (1 / COEF));
	p2.y = (p1.y + sin(g_game->player->rotationangle) * 20 * (1 / COEF));
	ft_draw_disque(&(g_game->img), g_game->player->x * COEF,
	g_game->player->y * COEF, 0xfff68f);
	p1.x *= COEF;
	p1.y *= COEF;
	p2.x *= COEF;
	p2.y *= COEF;
	ft_render_line(&(g_game->img), p1, p2, 0xf00000);
}

void			ft_set_player(char direct, int x, int y, t_cub *cub)
{
	if (!cub->direction)
	{
		cub->direction = direct;
		cub->map[x][y] = '0';
		cub->player_position[0] = x;
		cub->player_position[1] = y;
	}
	else
		get_err("Multiplayer or missing player\n");
}
