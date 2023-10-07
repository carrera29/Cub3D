#ifndef CUB3D_H
# define CUB3D_H

# include "libft.h"
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <math.h>
# include "MLX42.h"

# define SPEED 3

typedef struct s_cub t_cub;

typedef struct s_map
{
	char	**map;
	int		height;
	int		width;
	int		blaz;
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	double	angle;
	char	c_init;
	t_cub	*cub;
}			t_map;


typedef struct s_cub
{
	t_map	*map;
}			t_cub;


// Error
int	error_msg(t_cub *cub, char *msg);

// Parser
int	get_map(t_map *map, int fd);
int	find_the_exit(t_map *map, int y, int x, char c);

// Math
void	rotate_vectors(t_map *map, double x, double y);

#endif