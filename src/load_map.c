/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlima-nu <vlima-nu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 16:35:57 by vlima-nu          #+#    #+#             */
/*   Updated: 2021/10/25 20:17:13 by vlima-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	load_map(t_game *game, int fd)
{
	char	*swap;
	char	buffer[501];
	ssize_t	size;

	if (fd < 0)
		error(game, 0, 0);
	game->map_ber = ft_calloc(sizeof(char), 1);
	size = read(fd, buffer, 500);
	while (size > 0)
	{
		buffer[size] = 0;
		swap = ft_strdup(game->map_ber);
		free(game->map_ber);
		game->map_ber = ft_strjoin(swap, buffer);
		free(swap);
		size = read(fd, buffer, 500);
	}
	if (!game->map_ber)
		error(game, "Malloc to map failed", strerror(errno));
	close(fd);
	map_init(game);
}

int	check_input(int argc, char *argv)
{
	int	fd;

	fd = open(argv, 00);
	if (argc != 2)
		perror("Error\nInvalid number of arguments");
	else if (fd < 0)
		perror("Error\nCould not open the file");
	else if (ft_strcmp(".ber", argv + (ft_strlen(argv) - 4)))
		ft_putendl_fd("Error\nInvalid file extension. It must be *.ber", 2);
	else
		return (fd);
	if (fd != -1)
		close(fd);
	return (-1);
}
