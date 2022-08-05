/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlima-nu <vlima-nu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 10:36:36 by vlima-nu          #+#    #+#             */
/*   Updated: 2021/12/25 23:13:51 by vlima-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	hero_got_caught(t_game *game);

void	game_init(t_game *game)
{
	if (!game)
		error(0, "Malloc for game struct failed", strerror(errno));
	ft_bzero(&game->sprites, sizeof(t_sprites));
	ft_bzero(game, sizeof(t_game));
}

void	start_game(t_game *game)
{
	display_game(game);
	mlx_hook(game->screen, 17, 0L, close_window, game);
	mlx_expose_hook(game->screen, reload_image, game);
	mlx_key_hook(game->screen, key_press, game);
	mlx_loop_hook(game->mlx, animation, game);
	mlx_loop(game->mlx);
}

void	display_game(t_game *g)
{
	if (g->kills == g->enemies_num && !g->coins_num)
		g->door = 1;
	if (++g->frame == 8)
		g->frame = 0;
	draw_game(g);
	mlx_do_sync(g->mlx);
	mlx_put_image_to_window(g->mlx, g->screen, g->img, 0, 0);
	hero_got_caught(g);
	move_enemies(g);
	mlx_string_put(g->mlx, g->screen, 10, 10, C_WHITE, "Moves :");
	mlx_string_put(g->mlx, g->screen, 60, 10, C_WHITE, g->moves_str);
	ft_delay(45500);
}

/*
	Checks if the hero has been caught by an enemy.
*/
static void	hero_got_caught(t_game *g)
{
	int		i;

	i = 0;
	while (i < g->enemies_num)
	{
		if ((g->hero.coord.x == g->enemies[i].coord.x && \
			g->hero.coord.y == g->enemies[i].coord.y) || \
			(g->hero.coord.x == g->enemies[i].coord.x - \
			g->enemies[i].coord.to_x * 4 && \
			g->hero.coord.y == g->enemies[i].coord.y - \
			g->enemies[i].coord.to_y * 4) || \
			(g->hero.coord.x == g->enemies[i].coord.x + \
			g->enemies[i].coord.to_x * 4 && \
			g->hero.coord.y == g->enemies[i].coord.y + \
			g->enemies[i].coord.to_y * 4))
			exit_game(g, "You lose");
		i++;
	}
}

int	animation(t_game *game)
{
	game->hero.step = 0;
	display_game(game);
	return (0);
}
