/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollo <pollo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 18:16:33 by fmarin-p          #+#    #+#             */
/*   Updated: 2023/11/04 07:27:47 by pollo            ###   ########.fr       */
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
# define USAGE_ERROR			"Usage: ./cub3D [.cub extension map]"

# define RGB_ERROR				"Bad syntax for RGB color(s)"
# define EXT_ERROR				"Extension not valid"
# define EMPTYFILE_ERROR		"Empty file"
# define ELEM_ERROR				"Missing or extra element(s) found"
# define EMPTYMAP_ERROR			"Map content not found"
# define TEXTURESYNTAX_ERROR	"Incorrect texture(s) syntax"
# define TEXTUREPATH_ERROR		"Texture(s) path not valid"
# define WALL_ERROR				"Map walls not closed"
# define MAPNOTVALID_ERROR		"Map content not valid"

# define MLXINIT_ERROR			"MLX initialization failed"


// RESOLUTION
# define SCREENWIDTH			800
# define SCREENHEIGHT			600

# define FOV					0.90

// ELEMENT MASKS
enum e_element_masks
{
	NO_MASK	=	0b00000001,
	SO_MASK	=	0b00000010,
	WE_MASK	=	0b00000100,
	EA_MASK	=	0b00001000,
	F_MASK	=	0b00010000,
	C_MASK =	0b00100000,
	S_MASK =	0b01000000,
	ALL_MASK =	0b01111111
};

enum e_axis
{
	X,
	Y
};

enum e_map_dimensions
{
	WIDTH,
	HEIGHT
};

enum e_mapchar
{
	NORTH =		'N',
	SOUTH =		'S',
	EAST =		'E',
	WEST =		'W',
	SPACE =		'0',
	WALL =		'1'
};

enum e_textures
{
	NORTH_TEX,
	SOUTH_TEX,
	WEST_TEX,
	EAST_TEX,
	SPRITE_TEX,
	FLOOR_TEX,
	CEILING_TEX
};

typedef struct s_map
{
	char			**map;
	char			*texture_path[5];
	int				ceiling_color;
	int				floor_color;
	int				size[2];
	enum e_mapchar	initial_dir;
	int				initial_pos[2];

}		t_map;

typedef struct s_ray
{
	int				step[2];
	int				map[2];
	double			camera;
	double			raydir[2];
	double			side_dist[2];
	double			delta_dist[2];
	double			perpWallDist;
	int				start_draw;
	int				end_draw;

}					t_ray;

typedef struct s_cub
{
	t_map			*map_data;
	t_ray			*ray_data;
	mlx_t			*mlx;
	xpm_t			*texture[5];
	mlx_image_t		*image[7];
	double			pos[2];
	double			dir[2];
	double			plane[2];

}			t_cub;

// init/
	// check_map.c
int		check_map(t_map *map_data);

	// initialization.c
t_map	*load_map_data(int fd);
t_cub	*initialization(char *file);

	// load_from_file.c
char	**load_map(int fd);
void	load_texture_filename(char **texture, char *line);
void	load_rgb_color(int *color, char *line);

// mlx.c
int		start_game(t_cub *cub_data);

// raycasting.c
int		raycasting(t_cub *cub_data);

// other/
	// debug.c
void	print_data(t_cub *cub_data);

	// error.c
void	error(const char *msg, int perror_function);

	// free_mem.c
void	free_all(t_cub *cub_data);

#endif