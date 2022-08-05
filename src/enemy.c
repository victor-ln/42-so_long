/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlima-nu <vlima-nu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 15:33:25 by vlima-nu          #+#    #+#             */
/*   Updated: 2021/10/30 04:03:05 by vlima-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	enemy_can_move(t_enemies *enemy, char **map);

void	move_enemies(t_game *game)
{
	register int		i;

	i = -1;
	while (++i < game->enemies_num)
	{
		if (game->enemies[i].is_alive != 1)
			continue ;
		if (!enemy_can_move(game->enemies + i, game->map))
		{
			game->enemies[i].coord.dir = ft_rand() % 4;
			game->enemies[i].step = 0;
		}
		else if (++game->enemies[i].steps <= 8)
		{
			if (++game->enemies[i].step == 5)
				game->enemies[i].step = 1;
			game->enemies[i].coord.x += game->enemies[i].coord.to_x;
			game->enemies[i].coord.y += game->enemies[i].coord.to_y;
		}
		else
			game->enemies[i].steps = 0;
	}
}

static int	enemy_can_move(t_enemies *enemy, char **map)
{
	int		x;
	int		y;

	if (!enemy->steps)
	{
		x = enemy->coord.x / 32;
		y = enemy->coord.y / 32;
		set_dir(&enemy->coord);
		if (map[y + enemy->coord.to_y][x + enemy->coord.to_x])
			return (0);
		map[y][x] = 0;
		map[y + enemy->coord.to_y][x + enemy->coord.to_x] = ENEMY;
		enemy->coord.to_x *= 4;
		enemy->coord.to_y *= 4;
	}
	return (1);
}

void	enemy_death(t_game *g, int i)
{
	int		x;
	int		y;

	draw_sprite(g->img, \
		g->sprites.enemy_death[g->enemies[i].step], \
		g->enemies[i].coord.x, g->enemies[i].coord.y);
	if (++g->enemies[i].step == 6)
	{
		x = g->enemies[i].coord.x / 32;
		y = g->enemies[i].coord.y / 32;
		if (g->map[y][x] == ENEMY)
			g->map[y][x] = 0;
		else
			g->map[y + g->enemies[i].coord.to_y] \
				[x + g->enemies[i].coord.to_x] = 0;
		ft_bzero(g->enemies + i, sizeof(t_enemies));
		g->kills++;
	}
}
