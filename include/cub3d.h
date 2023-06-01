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
	char	init_pos;
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

#endif