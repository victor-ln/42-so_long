/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_environment.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlima-nu <vlima-nu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 04:04:16 by vlima-nu          #+#    #+#             */
/*   Updated: 2021/12/25 23:06:04 by vlima-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	load_sprites(t_sprites *sprites, void *mlx);
static int	a_sprite(t_img **image, void *mlx, char *path);
static int	a_set(t_img **ptr, void *mlx, char *path, int size);
static void	sprites_malloc(t_game *game);

void	load_environment(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		error(game, "Mlx init failed", strerror(errno));
	game->screen = mlx_new_window(game->mlx, game->width * 32, \
		game->height * 32, "so_long");
	if (!game->screen)
		error(game, "Could not open a window", strerror(errno));
	game->img = mlx_new_image(game->mlx, game->width * 32, game->height * 32);
	if (!game->img)
		error(game, "Could not create images", strerror(errno));
	sprites_malloc(game);
	if (load_sprites(&game->sprites, game->mlx))
		error(game, "Could not load all sprites", 0);
	game->moves_str = ft_utoa(0);
}

static void	sprites_malloc(t_game *g)
{
	int		i;

	g->sprites.treant = (t_img ***)malloc(sizeof(t_img **) * 4);
	g->sprites.mole = (t_img ***)malloc(sizeof(t_img **) * 4);
	g->sprites.hero = (t_img ***)malloc(sizeof(t_img **) * 4);
	g->sprites.enemy_death = (t_img **)malloc(sizeof(t_img *) * 6);
	g->sprites.coins = (t_img **)malloc(sizeof(t_img *) * 4);
	g->sprites.arrow = (t_img **)malloc(sizeof(t_img *) * 4);
	g->sprites.door = (t_img **)malloc(sizeof(t_img *) * 2);
	if (!g->sprites.hero || !g->sprites.coins || !g->sprites.arrow || \
		!g->sprites.door || !g->sprites.treant || \
		!g->sprites.enemy_death || !g->sprites.mole)
		error(g, "Malloc to images ptrs failed", strerror(errno));
	i = -1;
	ft_bzero(g->sprites.hero, sizeof(t_img *) * 4);
	ft_bzero(g->sprites.treant, sizeof(t_img *) * 4);
	ft_bzero(g->sprites.mole, sizeof(t_img *) * 4);
	while (++i < 4)
	{
		g->sprites.hero[i] = (t_img **)malloc(sizeof(t_img *) * 10);
		g->sprites.treant[i] = (t_img **)malloc(sizeof(t_img *) * 5);
		g->sprites.mole[i] = (t_img **)malloc(sizeof(t_img *) * 5);
		if (!g->sprites.treant[i] || !g->sprites.hero[i] || !g->sprites.mole[i])
			error(g, "Malloc to image ptrs failed", strerror(errno));
	}
}

static int	load_sprites(t_sprites *s, void *mlx)
{
	int		err;

	err = a_sprite(&s->grass, mlx, "/home/vlima-nu/42course/so_long/img/env/grass.xpm");
	err += a_sprite(&s->tree, mlx, "/home/vlima-nu/42course/so_long/img/env/tree.xpm");
	err += a_set(s->arrow, mlx, "/home/vlima-nu/42course/so_long/img/arrow/ .xpm", 4);
	err += a_set(s->door, mlx, "/home/vlima-nu/42course/so_long/img/env/door- .xpm", 2);
	err += a_set(s->coins, mlx, "/home/vlima-nu/42course/so_long/img/coins/coin- .xpm", 4);
	err += a_set(s->enemy_death, mlx, "/home/vlima-nu/42course/so_long/img/enemy-death/ .xpm", 6);
	err += a_set(s->hero[RIGHT], mlx, "/home/vlima-nu/42course/so_long/img/hero/right/ .xpm", 10);
	err += a_set(s->hero[LEFT], mlx, "/home/vlima-nu/42course/so_long/img/hero/left/ .xpm", 10);
	err += a_set(s->hero[DOWN], mlx, "/home/vlima-nu/42course/so_long/img/hero/down/ .xpm", 10);
	err += a_set(s->hero[UP], mlx, "/home/vlima-nu/42course/so_long/img/hero/up/ .xpm", 10);
	err += a_set(s->treant[RIGHT], mlx, "/home/vlima-nu/42course/so_long/img/treant/right/ .xpm", 5);
	err += a_set(s->treant[LEFT], mlx, "/home/vlima-nu/42course/so_long/img/treant/left/ .xpm", 5);
	err += a_set(s->treant[DOWN], mlx, "/home/vlima-nu/42course/so_long/img/treant/down/ .xpm", 5);
	err += a_set(s->treant[UP], mlx, "/home/vlima-nu/42course/so_long/img/treant/up/ .xpm", 5);
	err += a_set(s->mole[RIGHT], mlx, "/home/vlima-nu/42course/so_long/img/mole/right/ .xpm", 5);
	err += a_set(s->mole[LEFT], mlx, "/home/vlima-nu/42course/so_long/img/mole/left/ .xpm", 5);
	err += a_set(s->mole[DOWN], mlx, "/home/vlima-nu/42course/so_long/img/mole/down/ .xpm", 5);
	err += a_set(s->mole[UP], mlx, "/home/vlima-nu/42course/so_long/img/mole/up/ .xpm", 5);
	return (err);
}

static int	a_set(t_img **ptr, void *mlx, char *path, int size)
{
	char	*temp;
	int		errors;
	int		num;
	int		i;

	i = 0;
	errors = 0;
	temp = ft_strdup(path);
	if (!temp)
		return (1);
	num = ft_strlen(path) - 5;
	while (i < size)
	{
		temp[num] = '0' + i;
		errors += a_sprite(ptr + i, mlx, temp);
		i++;
	}
	free(temp);
	return (errors);
}

/*
	Loads a xpm file located in path to the image address pointer passed.
*/
static int	a_sprite(t_img **image, void *mlx, char *path)
{
	int		height;
	int		width;

	*(image) = mlx_xpm_file_to_image(mlx, path, &width, &height);
	if (!*(image))
		return (1);
	(*image)->height = height;
	(*image)->width = width;
	return (0);
}
