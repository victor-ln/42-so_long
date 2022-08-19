/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlima-nu <vlima-nu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 17:41:16 by vlima-nu          #+#    #+#             */
/*   Updated: 2022/08/19 18:12:17 by vlima-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	apply_changes(t_game *game);
static int	shoot_arrow(t_game *game);

int	key_press(int keycode, t_game *game)
{
	if (keycode == 'd')
		game->hero.coord.dir = RIGHT;
	else if (keycode == 'a')
		game->hero.coord.dir = LEFT;
	else if (keycode == 's')
		game->hero.coord.dir = DOWN;
	else if (keycode == 'w')
		game->hero.coord.dir = UP;
	else if (keycode == ' ')
		return (shoot_arrow(game));
	else if (keycode == ESC)
		exit_game(game, "Esc pressed");
	else
		return (0);
	game->hero.is_walking = 1;
	return (0);
}

int	key_release(int keycode, t_game *game)
{
	if (strchr("wasd", keycode))
		game->hero.is_walking = 0;
	return (0);
}

void	move_player(t_game *game)
{
	if (!game->hero.is_walking)
		return ;
	set_dir(&game->hero.coord);
	if (game->hero.coord.to_x && game->hero.coord.y % 32 > 28)
		return ;
	if (game->hero.coord.to_y && game->hero.coord.x % 32 > 28)
		return ;
	game->hero.coord.to_x *= 4;
	game->hero.coord.to_y *= 4;
	if (game->map[(game->hero.coord.y + game->hero.coord.to_y) / 32] \
			[(game->hero.coord.x + game->hero.coord.to_x) / 32] != 1)
	{
		game->hero.coord.x += game->hero.coord.to_x;
		game->hero.coord.y += game->hero.coord.to_y;
		if (++game->hero.step == 7)
			game->hero.step = 1;
		apply_changes(game);
	}
}

/*
	If the coins is where the player moved
	it decreases its variable.
	if coins is 0 and the player moved to the exit,
	then exits the game successfully.
*/
static void	apply_changes(t_game *game)
{
	int		x;
	int		y;

	x = game->hero.coord.x / 32;
	y = game->hero.coord.y / 32;
	free(game->moves_str);
	game->moves_str = ft_utoa(++game->moves_num);
	if (game->map[y][x] == COLL)
	{
		game->coins_num--;
		game->map[y][x] = 0;
	}
	else if (game->map[y][x] == EXIT)
		if (game->door)
			exit_game(game, "YOU WIN !");
}

static int	shoot_arrow(t_game *game)
{
	int		steps;

	game->hero.is_walking = 0;
	game->hero.step = 7;
	steps = game->hero.step;
	while (++steps < 12)
	{
		display_game(game);
		if (steps < 10)
			game->hero.step++;
		else
		{
			if (steps == 10)
				put_arrow(game);
			game->hero.step--;
		}
	}
	game->hero.step = 0;
	return (0);
}
