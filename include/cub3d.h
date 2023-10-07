/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmarin-p <fmarin-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 18:16:33 by fmarin-p          #+#    #+#             */
/*   Updated: 2023/10/07 18:29:45 by fmarin-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft.h"
# include "MLX42.h"
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <math.h>

# define GRID_SIZE 10
# define SPEED 3
# define X 0
# define Y 1

typedef struct s_cub	t_cub;

typedef enum e_mapchar
{
	NORTH = 'N',
	SOUTH = 'S',
	EAST = 'E',
	WEST = 'W',
	NOTHING = '0',
	WALL = '1',
	SPACE = ' ',
}			t_mapchar;

typedef struct s_map
{
	char	**map;
	int		height;
	int		width;
	int		blaz;
	double	pos[2];
	double	dir[2];
	double	plane[2];
	double	angle;
	char	c_init;
	t_cub	*cub;
}			t_map;

typedef struct s_cub
{
	t_map	*map;
}				t_cub;

// Error
int		error_msg(t_map *map, char *msg);

// Parser
int		get_map(t_map *map, int fd);
int		find_the_exit(t_map *map, int y, int x, char c);

// Math
void	rotate_vectors(t_map *map, double x, double y);

#endif