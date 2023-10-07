/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmarin-p <fmarin-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 10:28:58 by pollo             #+#    #+#             */
/*   Updated: 2023/10/07 18:29:57 by fmarin-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_map	*initialization(char *file)
{
	t_map	*map;
	int		fd;

	map = ft_calloc(1, sizeof(map));
	if (ft_strncmp(ft_strrchr(file, '.'), ".cub\0", 4))
		return (error_msg(map, "Extension not valid"));
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (error_msg(map, "Open fd"));
	if (get_map(&map, fd))
		return (1);
	find_the_exit(&map, map->pos[Y], map->pos[X], '.');
	find_the_exit(&map, map->pos[Y], map->pos[X], '0');
	map->map[(int)map->pos[Y]][(int)map->pos[X]] = map->c_init;
	return (0);
}

void printGrid(float playerX, float playerY, float dirX, float dirY, float planeX, float planeY) {
	char grid[GRID_SIZE][GRID_SIZE];

	// Inicializar la cuadrícula
	for (int i = 0; i < GRID_SIZE; i++) {
		for (int j = 0; j < GRID_SIZE; j++) {
			grid[i][j] = '-';
		}
	}

	// Marcar la posición del jugador
	int playerGridX = (int)playerX;
	int playerGridY = (int)playerY;
	if (playerGridX >= 0 && playerGridX < GRID_SIZE && playerGridY >= 0 && playerGridY < GRID_SIZE) {
		grid[playerGridY][playerGridX] = 'P';
	}

	// Marcar la dirección
	int dirGridX = (int)(playerX + dirX);
	int dirGridY = (int)(playerY + dirY);
	if (dirGridX >= 0 && dirGridX < GRID_SIZE && dirGridY >= 0 && dirGridY < GRID_SIZE) {
		grid[dirGridY][dirGridX] = 'D';
	}

	// Marcar el plano
	int planeGridX = (int)(playerX + planeX);
	int planeGridY = (int)(playerY + planeY);
	if (planeGridX >= 0 && planeGridX < GRID_SIZE && planeGridY >= 0 && planeGridY < GRID_SIZE) {
		grid[planeGridY][planeGridX] = 'V';
	}

	// Imprimir la cuadrícula
	for (int i = 0; i < GRID_SIZE; i++) {
		for (int j = 0; j < GRID_SIZE; j++) {
			printf("%c ", grid[i][j]);
		}
		printf("\n");
	}
}

int	main(int argc, char **argv)
{
	t_map	map;
	int		fd;

	if (argc != 2)
		return (printf("Usage: ./cub3D [.ber extension map]"), 1);
	return (0);
}
