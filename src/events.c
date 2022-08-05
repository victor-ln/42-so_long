/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlima-nu <vlima-nu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 17:41:16 by vlima-nu          #+#    #+#             */
/*   Updated: 2021/12/25 22:43:25 by vlima-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	apply_changes(t_game *game);
static void	move_player(t_game *game);
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
	move_player(game);
	return (0);
}

static void	move_player(t_game *game)
{
	int		steps;

	set_dir(&game->hero.coord);
	if (game->map[game->hero.coord.y / 32 + game->hero.coord.to_y] \
			[game->hero.coord.x / 32 + game->hero.coord.to_x] != 1)
	{
		steps = 0;
		game->hero.coord.to_x *= 4;
		game->hero.coord.to_y *= 4;
		while (steps <= 7)
		{
			game->hero.coord.x += game->hero.coord.to_x;
			game->hero.coord.y += game->hero.coord.to_y;
			if (++game->hero.step == 7)
				game->hero.step = 1;
			display_game(game);
			steps++;
		}
		apply_changes(game);
	}
	else
		display_game(game);
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

void	set_dir(t_coord *ptr)
{
	ptr->to_x = 0;
	ptr->to_y = 0;
	if (ptr->dir == RIGHT)
		ptr->to_x = 1;
	else if (ptr->dir == LEFT)
		ptr->to_x = -1;
	else if (ptr->dir == UP)
		ptr->to_y = -1;
	else
		ptr->to_y = 1;
}
