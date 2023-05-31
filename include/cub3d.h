#ifndef CUB3D_H
# define CUB3D_H

# include "libft.h"
# include <unistd.h>
# include <stdio.h>

typedef struct s_cub t_cub;

typedef struct s_map
{
	char	**map;
	int		p;
	int		p_x;
	int		p_y;
	t_cub	*cub;
}			t_map;


typedef struct s_cub
{
	t_map	*map;
}			t_cub;


// Error
int	error_msg(t_cub *cub, char *msg);

// Init
int	get_map(t_map *map, char *file);

#endif