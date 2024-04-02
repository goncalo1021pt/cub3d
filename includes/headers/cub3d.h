#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include "../.minilibx-linux/mlx.h"
# include "../.minilibx-linux/mlx_int.h"
# include "messages.h"
# include "display.h"
# include <errno.h>
# include <fcntl.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define W_WIDTH 1920
# define W_HEIGHT 1080

# define VALID_CHAR "01NSEW "
# define PLAYER "NSEW"

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

#endif
