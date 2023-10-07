/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmarin-p <fmarin-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 10:28:58 by pollo             #+#    #+#             */
/*   Updated: 2023/10/07 16:28:02 by fmarin-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#include <stdio.h>

#define GRID_SIZE 10

int	initialization(t_cub *cub, char *file)
{
	t_map	map;
	int		fd;

	(ft_memset(cub, 0, sizeof(cub)), ft_memset(&map, 0, sizeof(map)));
	(cub->map = &map, map.cub = cub);
	if (ft_strncmp(ft_strchr(file, '.'), ".cub\0", 5))
		return (error_msg(cub, "Wrong file name"));
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (error_msg(cub, "Open fd"));
	if (get_map(&map, fd))
		return (1);
	find_the_exit(&map, map.pos_y, map.pos_x, '.');
	find_the_exit(&map, map.pos_y, map.pos_x, '0');
	map.map[(int)map.pos_y][(int)map.pos_x] = map.c_init;
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

int main() {
    float playerX = 1.0f;    // Posición inicial del jugador en X
    float playerY = 2.0f;    // Posición inicial del jugador en Y
    float dirX = 1.0f;       // Componente X del vector de dirección
    float dirY = 0.0f;       // Componente Y del vector de dirección
    float planeX = 0.0f;     // Componente X del vector del plano
    float planeY = 1.0f;    // Componente Y del vector del plano

    printGrid(playerX, playerY, dirX, dirY, planeX, planeY);

    return 0;
}

// int	main(int argc, char **argv)
// {
// 	t_cub	cub;

// 	if (argc == 2)
// 	{
// 		initialization(&cub, argv[1]);
// 	}
// 	return (0);
// }
