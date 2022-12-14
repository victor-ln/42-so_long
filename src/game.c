/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlima-nu <vlima-nu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 10:36:36 by vlima-nu          #+#    #+#             */
/*   Updated: 2022/10/29 17:23:15 by vlima-nu         ###   ########.fr       */
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
	mlx_hook(game->screen, 2, 1, key_press, game);
	mlx_hook(game->screen, 3, 2, key_release, game);
	mlx_loop_hook(game->mlx, animation, game);
	mlx_loop(game->mlx);
}

void	display_game(t_game *game)
{
	if (game->kills == game->enemies_num && !game->coins_num)
		game->door = 1;
	if (++game->frame == 8)
		game->frame = 0;
	move_player(game);
	move_enemies(game);
	draw_game(game);
	mlx_do_sync(game->mlx);
	mlx_put_image_to_window(game->mlx, game->screen, game->img, 0, 0);
	mlx_string_put(game->mlx, game->screen, 10, 10, C_WHITE, "Moves :");
	mlx_string_put(game->mlx, game->screen, 60, 10, C_WHITE, game->moves_str);
	hero_got_caught(game);
	ft_delay(45500);
}

/*
	Checks if the hero has been caught by an enemy.
*/
static void	hero_got_caught(t_game *game)
{
	int		i;
	int		x[2];
	int		y[2];

	i = -1;
	x[1] = game->hero.coord.x / 32;
	y[1] = game->hero.coord.y / 32;
	while (++i < game->enemies_num)
	{
		if (game->enemies[i].is_alive != 1)
			continue ;
		x[0] = game->enemies[i].coord.x / 32;
		y[0] = game->enemies[i].coord.y / 32;
		if (x[0] == x[1] && y[0] == y[1])
			exit_game(game, "You lose");
	}
}

int	animation(t_game *game)
{
	if (!game->hero.is_walking)
		game->hero.step = 0;
	display_game(game);
	return (0);
}
