/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_game.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlima-nu <vlima-nu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 04:00:55 by vlima-nu          #+#    #+#             */
/*   Updated: 2021/10/27 15:59:19 by vlima-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	destroy_sprites(t_img **images, void *mlx, int x);
static void	destroy_ptrs(t_game *game);
static void	destroy_game(t_game *game);

void	error(t_game *game, char *message, char *str_error)
{
	if (message)
	{
		ft_putendl_fd("Error", 2);
		ft_putendl_fd(message, 2);
		ft_putendl_fd(str_error, 2);
	}
	if (game)
	{
		destroy_ptrs(game);
		destroy_game(game);
		if (game->mlx)
		{
			mlx_destroy_display(game->mlx);
			free(game->mlx);
		}
		free(game);
	}
	exit(EXIT_FAILURE);
}

void	exit_game(t_game *game, char *message)
{
	ft_putendl_fd(message, 1);
	destroy_ptrs(game);
	destroy_game(game);
	mlx_destroy_display(game->mlx);
	free(game->mlx);
	free(game);
	exit(EXIT_SUCCESS);
}

static void	destroy_sprites(t_img **images, void *mlx, int x)
{
	int		i;

	i = 0;
	if (images)
	{
		while (i < x)
		{
			if (images[i])
				mlx_destroy_image(mlx, images[i]);
			i++;
		}
		free(images);
	}
}

static void	destroy_game(t_game *game)
{
	if (game->sprites.door)
		destroy_sprites(game->sprites.door, game->mlx, 2);
	if (game->sprites.coins)
		destroy_sprites(game->sprites.coins, game->mlx, 4);
	if (game->sprites.arrow)
		destroy_sprites(game->sprites.arrow, game->mlx, 4);
	if (game->sprites.enemy_death)
		destroy_sprites(game->sprites.enemy_death, game->mlx, 6);
	if (game->moves_str)
		free(game->moves_str);
	if (game->arrow)
		free(game->arrow);
	if (game->enemies)
		free(game->enemies);
	if (game->sprites.hero)
		free(game->sprites.hero);
	if (game->sprites.grass)
		mlx_destroy_image(game->mlx, game->sprites.grass);
	if (game->sprites.tree)
		mlx_destroy_image(game->mlx, game->sprites.tree);
	if (game->img)
		mlx_destroy_image(game->mlx, game->img);
	if (game->screen)
		mlx_destroy_window(game->mlx, game->screen);
}

static void	destroy_ptrs(t_game *game)
{
	int		i;

	if (game->map)
	{
		while (game->height)
			if (game->map[--game->height])
				free(game->map[game->height]);
		free(game->map);
	}
	else
		free(game->map_ber);
	i = -1;
	while (++i < 4)
	{
		if (game->sprites.hero)
			destroy_sprites(game->sprites.hero[i], game->mlx, 10);
		if (game->sprites.treant)
			destroy_sprites(game->sprites.treant[i], game->mlx, 5);
		if (game->sprites.mole)
			destroy_sprites(game->sprites.mole[i], game->mlx, 5);
	}
	if (game->sprites.treant)
		free(game->sprites.treant);
	if (game->sprites.mole)
		free(game->sprites.mole);
}
