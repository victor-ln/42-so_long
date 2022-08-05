/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlima-nu <vlima-nu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 15:20:03 by vlima-nu          #+#    #+#             */
/*   Updated: 2021/10/30 03:32:36 by vlima-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void			draw_players(t_game *game);
static void			draw_pixel(t_img *image, int x, int y, unsigned int color);
static unsigned int	get_color(t_img *image, int x, int y);

void	draw_game(t_game *game)
{
	register int		x;
	register int		y;

	y = 0;
	while (y < game->height)
	{
		x = 0;
		while (x < game->width)
		{
			draw_sprite(game->img, game->sprites.grass, x * 32, y * 32);
			if (game->map[y][x] == 1)
				draw_sprite(game->img, game->sprites.tree, x * 32, y * 32);
			else if (game->map[y][x] == COLL)
				draw_sprite(game->img, game->sprites.coins[game->frame / 2], \
					x * 32, y * 32);
			else if (game->map[y][x] == EXIT)
				draw_sprite(game->img, game->sprites.door[game->door], \
					x * 32, y * 32);
			x++;
		}
		y++;
	}
	draw_players(game);
	draw_arrows(game);
}

/*
	Draws the hero and enemies (if they exist), based in their specific coordinates.
*/
static void	draw_players(t_game *g)
{
	int		i;

	i = -1;
	draw_sprite(g->img, \
		g->sprites.hero[g->hero.coord.dir][g->hero.step], \
		g->hero.coord.x, g->hero.coord.y);
	while (++i < g->enemies_num)
	{
		if (!g->enemies[i].is_alive)
			continue ;
		else if (g->enemies[i].is_alive < 0)
			enemy_death(g, i);
		else if (g->enemies[i].who)
			draw_sprite(g->img, g->sprites.treant[g->enemies[i].coord.dir] \
				[g->enemies[i].step], g->enemies[i].coord.x, \
					g->enemies[i].coord.y);
		else
			draw_sprite(g->img, g->sprites.mole[g->enemies[i].coord.dir] \
				[g->enemies[i].step], g->enemies[i].coord.x, \
					g->enemies[i].coord.y);
	}
}

void	draw_sprite(t_img *image, t_img *sprite, int x, int y)
{
	register int		i;
	register int		j;

	j = 0;
	while (j < sprite->height)
	{
		i = 0;
		while (i < sprite->width)
		{
			draw_pixel(image, x + i, y + j, get_color(sprite, i, j));
			i++;
		}
		j++;
	}
}

/*
	Draws the color in (x, y) position of the image.
*/
static void	draw_pixel(t_img *img, int x, int y, unsigned int color)
{
	if (color != C_NONE)
		*(unsigned int *)
			((img->data + (x * img->bpp / 8 + y * img->size_line))) = color;
}

/*
	Returns the pixel color of (x, y) position of the image.
*/
static unsigned int	get_color(t_img *img, int x, int y)
{
	return ((*(unsigned int *)
			(img->data + (x * img->bpp / 8 + y * img->size_line))));
}
