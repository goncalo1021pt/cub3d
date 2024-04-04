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
# define ROTATION_SPEED 45
# define PI 3.14159265358979323846

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

typedef enum e_keys
{
	ESC = 65307,
	W = 119,
	A = 97,
	S = 115,
	D = 100,
	LEFT_ARROW = 65361,
	RIGHT_ARROW = 65363
}			t_keys;

typedef enum e_dir
{
	SOUTH = 0,
	EAST = 90,
	NORTH = 180,
	WEST = 270
}			t_dir;

typedef struct s_player
{
	int		x;
	int		y;
	double	angle;
}			t_player;
// parser.c
bool		validate_map(t_map *map);
bool		parser(int argc, char **argv, t_map *map);

// map_aux.c
void		free_file(char **arr_str);
void		print_file(t_map *map);
void		print_grid(char **grid);
void		init_map(t_map *map);
void				print_player(t_player *player);

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
bool		create_grid(t_map *map);

// player_movment.c
void		initialize_player(t_player *player, t_map *map);
void		rotate_player(t_player *player, int angle);
void		move_player(t_player *player, t_map *map, int speed, t_dir dir);

// start.c
bool		start_game(t_map *map);

#endif