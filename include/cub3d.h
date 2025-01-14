/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmarin-p <fmarin-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 18:16:33 by fmarin-p          #+#    #+#             */
/*   Updated: 2024/01/16 15:07:30 by fmarin-p         ###   ########.fr       */
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
# define SCREENWIDTH			1024
# define SCREENHEIGHT			768

// GAME OPTIONS
# define FOV					0.90
# define HITBOX					0.7
# define MOVE_SPEED				3.0
# define SPRINT_SPEED			0.05
# define ROTATION_SPEED			2.0
# define MOUSE_ACC				0.0015
# define DOOR_SPEED				0.8

// MINIMAP
# define MINIMAP_TILES			5.0

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
	WALL =		'1',
	DOOR =		'D',
	OP_DOOR =	'O'
};

enum e_door
{
	WAIT_DOOR,
	OPENING_DOOR,
	OPEN_DOOR,
	CLOSING_DOOR
};

enum e_xpm
{
	NORTH_TEX,
	SOUTH_TEX,
	WEST_TEX,
	EAST_TEX,
	SPRITE_TEX,
	DOOR_TEX,
	DOORJAM_TEX
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
	int				ray_pos[2];
	double			camera;
	double			raydir[2];
	double			side_dist[2];
	double			delta_dist[2];
	double			perp_wall_dist;
	int				side;
	int				line_height;
	int				start_draw;
	int				end_draw;
	int				wall_texture;

}					t_ray;

typedef struct s_cub
{
	t_map			*map_data;
	mlx_t			*mlx;
	xpm_t			*xpm[7];
	mlx_image_t		*screen;
	mlx_image_t		*minimap;
	double			**door_state;
	int				center[2];
	double			pos[2];
	double			dir[2];
	double			plane[2];
	double			move_speed;
	double			rot_speed;
	double			door_speed;

}			t_cub;

// init/
	// check_map.c
int			check_map(t_map *map_data);

	// initialization.c
t_map		*load_map_data(int fd);
t_cub		*initialization(char *file);

	// load_from_file.c
char		**load_map(int fd);
void		load_texture_filename(char **texture, char *line);
void		load_rgb_color(int *color, char *line);

// game/
	// mlx.c
int			start_game(t_cub *cub_data);

	// raycasting.c
int			raycasting(t_cub *cub_data);

	// screen_rendering.c
int			select_texture(t_ray *ray, double *pos, char **map);
int			render_screen(t_cub *cub_data, t_ray ry, int screen_pos);

	// player.c
void		rotate(t_cub *cub_data, double rot_speed);
void		move(t_cub *cub_data, char **map, double dirX, double dirY);

	// hooks.c
int			mouse_hook(t_cub *cub_data, mlx_t *mlx, double rot_speed);
void		loop_hook(void *param);

	// minimap.c
int			render_minimap(t_cub *cub_data, mlx_t *mlx, t_map *map_data);
int			render_minimap_hub(mlx_t *mlx);

	// minimap_utils.c
mlx_image_t	*init_minimap(mlx_t *mlx);
mlx_image_t	*init_arrow(mlx_t *mlx, mlx_image_t *minimap);
int			check_boundaries(double *map_pos, t_map *map_data);

	// doors.c
void		door_animation(t_cub *cub_data, double *pos, char **map);	

// other/
	// debug.c
void		print_data(t_cub *cub_data);

	// error.c
void		error(const char *msg, int perror_function);

	// free_mem.c
void		free_all(t_cub *cub_data);

#endif