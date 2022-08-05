/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validate.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlima-nu <vlima-nu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 15:40:17 by vlima-nu          #+#    #+#             */
/*   Updated: 2021/10/27 14:08:31 by vlima-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

typedef struct s_map_validate
{
	int		exits_num;
	int		heros_num;
	int		coins_num;
	int		zeros_num;
	int		i;
}	t_map_validate;

static void	is_valid(t_game *game, t_map_validate *map);
static int	is_border(t_game *game, int i);
static void	is_rectangular(t_game *game);

/*

A map example:

1 1 1 1 1 \n
1 0 P C 1 \n
1 0 0 C 1 \n
1 E 1 C 1 \n
1 1 1 1 1 \0

*/

void	map_validate(t_game *game)
{
	t_map_validate	map;

	is_rectangular(game);
	ft_bzero(&map, sizeof(t_map_validate));
	while (game->map_ber[map.i])
	{
		if (is_border(game, map.i))
		{
			if (game->map_ber[map.i] != '1')
				error(game, "Invalid map, it's not surrounded by walls", 0);
		}
		else
			is_valid(game, &map);
		map.i++;
	}
	if (map.exits_num != 1 || map.heros_num != 1 || !map.coins_num)
		error(game, "Invalid map, must have 1 exit, 1 player and collects", 0);
	if (!map.zeros_num)
		error(game, "Invalid map, must have free spaces too", 0);
	game->coins_num = map.coins_num;
}

/*
	Calculates the width and the height of the map and then
	checks if the map is symmetrical and rectangular.
*/
static void	is_rectangular(t_game *game)
{
	int		i;

	i = 0;
	game->height = 1;
	while (game->map_ber[i])
	{
		if (game->map_ber[i] == '\n')
			game->height++;
		if (game->height == 1)
			game->width++;
		i++;
	}
	if (!i)
		error(game, "Invalid map, it is empty", 0);
	else if (i - (game->height - 1) != game->width * game->height)
		error(game, "Invalid map, it's not symmetrical", 0);
	else if (game->width == game->height)
		error(game, "Invalid map, it's not rectangular", 0);
}

static void	is_valid(t_game *game, t_map_validate *map)
{
	if (game->map_ber[map->i] == '1')
		return ;
	else if (game->map_ber[map->i] == '0')
		map->zeros_num++;
	else if (game->map_ber[map->i] == 'C')
		map->coins_num++;
	else if (game->map_ber[map->i] == 'E')
		map->exits_num++;
	else if (game->map_ber[map->i] == 'P')
		map->heros_num++;
	else if (game->map_ber[map->i] != '\n')
		error(game, "Invalid map, it has an invalid character", 0);
}

static int	is_border(t_game *game, int i)
{
	if (i < game->width
		|| (i % (game->width + 1) == 0)
		|| (i % (game->width + 1) == (game->width - 1))
		|| (i > (game->width + 1) * (game->height - 1)))
	{
		return (1);
	}
	return (0);
}
