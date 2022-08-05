/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlima-nu <vlima-nu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 04:00:18 by vlima-nu          #+#    #+#             */
/*   Updated: 2021/10/30 03:37:48 by vlima-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "so_long_data.h"

/*
	Checks if there's just one argument to be read,
	Opens the file, checks file extension and file descriptor
	and returns the file descriptor or -1 if there is an error.
*/
int			check_input(int argc, char *argv);

/*
	Saves the content of the opened file in a char pointer
	and calls map_init.
*/
void		load_map(t_game *game, int fd);

/*
	Gets map information and creates a matrix of the map.
	Searches in the map free spaces to put enemies and
	gets the coordinates of the player and enemies on the map.
*/
void		map_init(t_game *game);

/*
	Checks if map has at least one player,
	one exit, and collects, if is rectangular and symmetrical,
	if it's surrounded by walls "1"
	and if there's only the "01PEC\\n" chars.
*/
void		map_validate(t_game *game);

/*
	Writes the message passed, frees the map pointer 
	and exits the game with status 1.
*/
void		exit_game(t_game *game, char *message);

/*
	Draws pixel per pixel each map point with their respectives sprites.
*/
void		draw_game(t_game *game);

/*
	Exits the game if close_window box is clicked.
*/
int			close_window(t_game *game);

/*
	Controls where to move when keycode is a, s, d or w
	or exits the game if ESC is pressed.
*/
int			key_press(int keycode, t_game *game);

/*
	Displays the map with the player and enemies if they exist and
	the number of movements done on the screen.
*/
void		display_game(t_game *game);

/*
	Writes "Error\\n" and the messages passed, frees
	all allocated memory and exits with status 1.
*/
void		error(t_game *game, char *message, char *str_error);

/*
	Initializes display, opens a window, creates an image and loads all sprites.
	Exits the game appropriately if any error occurs.
*/
void		load_environment(t_game *game);

/*
	Keeps game in loop even without a hook,
	rendering coins and enemies moving.
*/
int			animation(t_game *game);

/*
	Checks if enemies can move to a random direction. If they can it moves,
	else it changes to another random direction;
*/
void		move_enemies(t_game *game);

/*
	Calls the Mlx functions.
*/
void		start_game(t_game *game);

/*
	Reloads map and the initial player position.
*/
void		reboot_game(t_game *game);

/*
	Sets all game struct variables to zero.
*/
void		game_init(t_game *game);

int			reload_image(t_game *game);

void		draw_arrows(t_game *game);

void		put_arrow(t_game *game);

/*
	Receives the image to be drawn and the sprite
	to draw at (x * sprite width, y * sprite height) position of the image.
*/
void		draw_sprite(t_img *image, t_img *sprite, int x, int y);

void		enemy_death(t_game *game, int i);

void		set_dir(t_coord *ptr);

#endif
