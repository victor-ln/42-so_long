/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrows.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlima-nu <vlima-nu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 17:57:09 by vlima-nu          #+#    #+#             */
/*   Updated: 2021/10/30 04:01:19 by vlima-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	hit_enemies(t_game *game, int i);
static void	move_arrows(t_game *game);
static void	realloc_arrows(t_coord **arrows, short arrows_num);

void	draw_arrows(t_game *game)
{
	int		i;
	int		j;

	i = 0;
	j = game->arrows_num;
	if (game->arrows_num)
	{
		move_arrows(game);
		while (i < j)
		{
			if (game->arrow[i].x && game->arrow[i].y)
				draw_sprite(game->img, game->sprites.arrow[game->arrow[i].dir], \
					game->arrow[i].x, game->arrow[i].y);
			i++;
		}
	}
	if (!game->arrows_num && game->arrow)
	{
		free(game->arrow);
		game->arrow = 0;
	}
}

void	put_arrow(t_game *game)
{
	int		current;

	current = game->arrows_num;
	if (!game->arrow)
		game->arrow = (t_coord *)malloc(sizeof(t_coord) * ++game->arrows_num);
	else
		realloc_arrows(&game->arrow, game->arrows_num++);
	if (!game->arrow)
		error(game, "Malloc for arrows struct failed", strerror(errno));
	game->arrow[current].dir = game->hero.coord.dir;
	game->arrow[current].x = game->hero.coord.x;
	game->arrow[current].y = game->hero.coord.y;
	set_dir(game->arrow + current);
	game->arrow[current].to_x *= 8;
	game->arrow[current].to_y *= 8;
}

static void	realloc_arrows(t_coord **arrows, short arrows_num)
{
	void	*bkp;
	short	size;

	size = arrows_num;
	bkp = malloc(sizeof(t_coord) * size);
	ft_memcpy(bkp, *arrows, sizeof(t_coord) * size);
	free(*arrows);
	*arrows = (t_coord *)malloc(sizeof(t_coord) * ++size);
	ft_memcpy(*arrows, bkp, sizeof(t_coord) * (size - 1));
	free(bkp);
}

static void	move_arrows(t_game *g)
{
	int		x;
	int		y;
	int		i;
	int		j;

	i = -1;
	j = g->arrows_num;
	while (++i < j)
	{
		if (!g->arrow[i].x && !g->arrow[i].y)
			continue ;
		x = g->arrow[i].x / 32;
		y = g->arrow[i].y / 32;
		if ((g->map[y][x] && g->map[y][x] != ENEMY) || hit_enemies(g, i))
		{
			g->arrows_num--;
			ft_bzero(g->arrow + i, sizeof(t_coord));
		}
		else
		{
			g->arrow[i].x += g->arrow[i].to_x;
			g->arrow[i].y += g->arrow[i].to_y;
		}
	}
}

static int	hit_enemies(t_game *g, int j)
{
	int		i;

	i = 0;
	while (i < g->enemies_num)
	{
		if ((g->arrow[j].x == g->enemies[i].coord.x && \
			g->arrow[j].y == g->enemies[i].coord.y) || \
			(g->arrow[j].x - g->arrow[j].to_x == g->enemies[i].coord.x && \
			g->arrow[j].y - g->arrow[j].to_y == g->enemies[i].coord.y) || \
			((g->arrow[j].x + g->arrow[j].to_x == g->enemies[i].coord.x && \
			g->arrow[j].y + g->arrow[j].to_y == g->enemies[i].coord.y)))
		{
			g->enemies[i].is_alive = -1;
			g->enemies[i].step = 0;
			return (1);
		}
		i++;
	}
	return (0);
}
