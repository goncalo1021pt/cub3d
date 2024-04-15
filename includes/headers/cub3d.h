#ifndef CUB3D_H
# define CUB3D_H

# include "../.minilibx-linux/mlx.h"
# include "../.minilibx-linux/mlx_int.h"
# include "../libft/libft.h"
# include "messages.h"
# include "structs.h"
# include <errno.h>
# include <fcntl.h>
# include <math.h>
# include <time.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define W_WIDTH 1920
# define W_HEIGHT 1080

# define VALID_CHAR "01NSEW "
# define PLAYER "NSEW"
# define MAP_SCALE 64
# define ROTATION_SPEED 5
# define SPEED_MULTIPLIER 2
# define PI 3.14159265358979323846
# define MOUSE_SENSITIVITY 250
# define ESC 65307
# define UP 65362
# define DOWN 65364
# define LEFT 65361
# define RIGHT 65363
# define PAUSE 0

typedef enum e_keys_angle
{
	W_ANGLE = 0,
	A_ANGLE = 270,
	S_ANGLE = 180,
	D_ANGLE = 90,
}		t_keys_angle;

typedef enum e_dir
{
	EAST = 0,
	SOUTH = 90,
	WEST = 180,
	NORTH = 270
}		t_dir;

typedef enum e_key_arr
{
	W,
	S,
	A, 
 	D,
	P,
	L_SHIFT,
	LEFT_ARROW,
	RIGHT_ARROW
}	t_key_arr;

// parser.c
bool	validate_map(t_map *map);
bool	parser(int argc, char **argv, t_map *map);

// map_aux.c
void	free_file(char **arr_str);
void	print_file(t_map *map);
void	print_grid(char **grid);
void	init_map(t_map *map);
void	print_player(t_player *player);

// textures.c
bool	get_args(t_map *map);

// aux.c
bool	is_in_array(char *arr, char c);

// map_check.c
bool	check_char(t_map *map);
bool	initiate_flood(t_map *map);
bool	check_sorroundings(t_map *map);

// textures_check.c
bool	validate_textures(t_map *map);
int		ft_strslen(char **strs);

// movment_grid.c
bool	create_grid(t_map *map);

//player.c
void	update_player(t_session *instance, int x, int y);

// player_movment.c
void	initialize_player(t_player *player, t_map *map);
void	rotate_player(t_player *player, int angle);
void	move_player(t_player *player, t_map *map, int speed, t_keys_angle dir);
float	get_player_speed(t_session *instance);

// display.c
void	mlx_startup(t_session *instance);
void	mlx_update(t_session *instance);
void	mlx_shutdown(t_session *instance);

// hooks.c
int		handle_key(int keycode, t_session *instance);
int		const_movement(t_session *instance);
int		handle_key_release(int keycode, t_session *instance);
int		exit_hook(t_session *instance);

// mouse_hooks.c
int		mouse_movement(int x, int y, t_session *instance);

// draw.c
void	pixel_put(t_data *data, int x, int y, int color);
void	init_dda(t_dda *dda, t_point start, t_point end);
void	draw_line(t_session *instance, t_point start, t_point end, int color);
void	draw_square(t_session *instance, t_point point, int sq, int color);
void 	draw_face(t_session *instance, int x, int y, int color);
void	clear_image(t_session *instance, int color);

// grid.c // debug2D.c
void	debug2D(t_session *instance);
//minimap.c
void 	vp_grid(t_session *instance);
void 	vp_scaled(t_session *instance);
void	vp_player(t_session *instance, int x, int y);


// start.c
bool	start_game(t_session *instance);
// main.c
void	clean_parser(t_map *map);
#endif
