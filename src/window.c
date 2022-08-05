/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlima-nu <vlima-nu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 18:18:37 by vlima-nu          #+#    #+#             */
/*   Updated: 2021/10/26 18:18:59 by vlima-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	reload_image(t_game *game)
{
	mlx_put_image_to_window(game->mlx, game->screen, game->img, 0, 0);
	return (0);
}

int	close_window(t_game *game)
{
	exit_game(game, "Window closed");
	return (0);
}
