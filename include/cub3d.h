/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmarin-p <fmarin-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 18:16:33 by fmarin-p          #+#    #+#             */
/*   Updated: 2023/10/21 01:31:21 by fmarin-p         ###   ########.fr       */
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

// ERROR MESAGGES
# define RGB_ERROR				"Bad syntax for RGB color(s)"
# define EXT_ERROR				"Extension not valid"
# define EMPTYFILE_ERROR		"Empty file"
# define MISSINGELEM_ERROR		"Element(s) missing"
# define EXTRAELEM_ERROR		"Extra element(s) found"
# define EMPTYMAP_ERROR			"Map content not found"
# define TEXTURESYNTAX_ERROR	"Incorrect texture(s) syntax"

// ELEMENT MASKS
# define NO_MASK	0b00000001
# define SO_MASK	0b00000010
# define WE_MASK	0b00000100
# define EA_MASK	0b00001000
# define F_MASK		0b00010000
# define C_MASK		0b00100000
# define ALL_MASK	0b00111111

// AXIS
# define X 0
# define Y 1

// MAP SIZE
# define WIDTH 0
# define HEIGHT 1

// RESOLUTION
# define SCREENWIDTH	800
# define SCREENHEIGHT	600

typedef struct s_cub	t_cub;

typedef enum e_mapchar
{
	NORTH =		'N',
	SOUTH =		'S',
	EAST =		'E',
	WEST =		'W',
	NOTHING =	'0',
	WALL =		'1',
	SPACE =		' '

}			t_mapchar;

typedef struct s_map
{
	char	**map;
	char	*north_texture;
	char	*south_texture;
	char	*west_texture;
	char	*east_texture;
	int		ceiling_color;
	int		floor_color;
	int		size[2];

}		t_map;

typedef struct s_cub
{
	t_map	*map_data;
	int		height;
	int		width;
	double	pos[2];
	double	dir[2];
	double	plane[2];

}			t_cub;


// debug.c
void	print_data(t_cub *cub_data);

// error.c
void	error(char *msg, int perror_function);

// load_map.c
char	**load_map(int fd);
int		check_for_elements(t_map *map_data, char *line);

// check_map.c
int		check_map(t_map *map_data);

// initialization.c
t_map	*load_map_data(int fd);
t_cub	*initialization(char *file);

// rgb.c
void	load_rgb_color(int *color, char *line);

// Math
void	rotate_vectors(t_map *map, double x, double y);

#endif