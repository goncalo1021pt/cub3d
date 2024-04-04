#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include "../.minilibx-linux/mlx.h"
# include "../.minilibx-linux/mlx_int.h"
# include "messages.h"
# include "structs.h"
# include <errno.h>
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define W_WIDTH 1920
# define W_HEIGHT 1080

# define VALID_CHAR "01NSEW "
# define PLAYER "NSEW"
# define MAP_SCALE 32
# define ROTATION_SPEED 45
# define PI 3.14159265358979323846

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

// parser.c
bool		validate_map(t_map *map);
bool		parser(int argc, char **argv, t_map *map);

// map_aux.c
void		free_file(char **arr_str);
void		print_file(t_map *map);
void		print_grid(char **grid);
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
bool		create_grid(t_map *map);

//player.c

// player_movment.c
void		initialize_player(t_player *player, t_map *map);
void		rotate_player(t_player *player, int angle);
void		move_player(t_player *player, t_map *map, int speed, t_dir dir);

// display.c
void	mlx_startup(t_session *instance);
void	mlx_update(t_session *instance);
void	mlx_shutdown(t_session *instance);
void	pixel_put(t_data *data, int x, int y, int color);

// hooks.c
int		handle_key(int keycode, t_session *instance);
int		exit_hook(t_session *instance);

// draw.c
void	init_dda(t_dda *dda, int start_x, int start_y , int end_x, int end_y);
void	draw_line(t_session *instance, int start_x, int end_x, int start_y, int end_y);

// grid.c
void	draw_player(t_session *instance, t_point pos);
void 	draw_grid(t_session *instance);
t_point spawn_point(t_session *instance);
// start.c
bool		start_game(t_map *map);

#endif
