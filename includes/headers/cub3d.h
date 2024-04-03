#ifndef CUB3D_H
# define CUB3D_H

# include "../.minilibx-linux/mlx.h"
# include "../libft/libft.h"
# include "messages.h"
# include <errno.h>
# include <fcntl.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define VALID_CHAR "01NSEW "
# define PLAYER "NSEW"
# define MAP_SCALE 32

typedef struct s_map
{
	char	**buffer;
	char	**grid;
	char	**map;
	bool	**visited;
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	char	*c;
	char	*f;
}			t_map;

// parser.c
bool		validate_map(t_map *map);
bool		parser(int argc, char **argv, t_map *map);

// map_aux.c
void		free_file(char **arr_str);
void		print_file(t_map *map);
void		init_map(t_map *map);

// textures.c
bool		get_args(t_map *map);

// aux.c
bool		is_in_array(char *arr, char c);

// map_check.c
bool		check_char(t_map *map);
bool		initiate_flood(t_map *map);
bool		check_sorroundings(t_map *map);

// textures_check.c
bool		validate_textures(t_map *map);
int			ft_strslen(char **strs);

// movment_grid.c
bool	create_grid(t_map *map);

#endif