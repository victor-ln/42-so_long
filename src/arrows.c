/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrows.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlima-nu <vlima-nu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 17:57:09 by vlima-nu          #+#    #+#             */
/*   Updated: 2022/10/29 17:37:54 by vlima-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	hit_enemies(t_enemies *enemies, int enemies_nbr, t_coord *arw);
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
		if ((g->map[y][x] && g->map[y][x] != ENEMY) || \
			hit_enemies(g->enemies, g->enemies_num, g->arrow + i))
		{
			if (--g->arrows_num)
				memmove(g->arrow + i, g->arrow + i + 1, \
					(g->arrows_num - i) * sizeof(t_coord));
		}
		else
		{
			g->arrow[i].x += g->arrow[i].to_x;
			g->arrow[i].y += g->arrow[i].to_y;
		}
	}
}

static int	hit_enemies(t_enemies *enemies, int enemies_nbr, t_coord *arw)
{
	int		i;

	i = -1;
	while (++i < enemies_nbr)
	{
		if (enemies[i].is_alive != 1)
			continue ;
		if ((arw->x == enemies[i].coord.x && arw->y == enemies[i].coord.y) || \
			(arw->x - arw->to_x == enemies[i].coord.x && \
			arw->y - arw->to_y == enemies[i].coord.y) || \
			((arw->x + arw->to_x == enemies[i].coord.x && \
			arw->y + arw->to_y == enemies[i].coord.y)))
		{
			enemies[i].is_alive = -1;
			enemies[i].step = 0;
			return (1);
		}
	}
	return (0);
}
