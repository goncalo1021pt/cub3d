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
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <time.h>
# include <unistd.h>

# define W_WIDTH 2560
# define W_HEIGHT 1440

# define VALID_CHAR "01NSEWD "
# define PLAYER "NSEW"
# define MAP_SCALE 64
# define PLAYER_SIZE 2
# define ROTATION_SPEED 5
# define SPEED_MULTIPLIER 2
# define PI 3.14159265358979323846
# define MOUSE_SENSITIVITY 200
# define FPS 120
# define FRAME_TIME 8333.33333

typedef enum e_mode_type
{
	DEFAULT,
	PLAY,
	PAUSE,
	MAIN_MENU,
	MINIMAP
}		t_mode_type;

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
	TAB,
	L_SHIFT,
	LEFT_ARROW,
	RIGHT_ARROW
}		t_key_arr;

typedef enum e_sprite_order
{
	NORTH_TEXTURE,
	SOUTH_TEXTURE,
	EAST_TEXTURE,
	WEST_TEXTURE,
	DOOR_TEXTURE_1,
	DOOR_TEXTURE_2,
	DOOR_TEXTURE_3,
	DOOR_TEXTURE_4,
	DOOR_TEXTURE_5,
	DOOR_TEXTURE,
}		t_sprite_order;

// parser.c
bool	validate_map(t_map *map);
bool	check_doors(t_map *map);
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
int		ft_strslen(char **strs);
bool	is_number(char *str);
int		get_hexa_color(char *color);
void	free_prev(char **arr_str, int ctd);
int		min(int n1, int n2);
int		max(int n1, int n2);
bool	is_in_colision(int x, int y, t_session *instance, char type);
void	check_time(void);

// map_check.c
bool	check_char(t_map *map);
bool	initiate_flood(t_map *map);
bool	check_sorroundings(t_map *map);
void	create_boarder(char **grid);

// textures_check.c
bool	validate_textures(t_map *map);

// movment_grid.c
bool	create_grid(t_map *map);

//Camera3D.c
void	camera3d(t_session *instance, double pos_x, double pos_y);
//raycaster.c
void	init_ray(t_camera3D *camera, t_ray *ray, int i, t_point pos);
void	aim_ray(t_ray *ray, double pos_x, double pos_y);
void	cast_ray(t_session *instance, t_ray *ray);
void	cast_aux_ray(t_session *instance, t_ray *ray);

//raycaster_utils.c
double	clamp_ray(double dir);
double	get_pwall_distance(t_ray *ray);
int		get_wall_dir(char **grid, int x, int y, int side);
int		get_walx(t_ray *ray, double pos_x, double pos_y);
t_data	*get_tex_data(t_session *instance, t_ray *ray, bool select);

// player_movment.c
bool	initialize_player(t_player *player, t_map *map);
void	rotate_player(t_player *player, int angle);
void	move_player(t_player *player, t_session *instance, int speed,
			t_keys_angle dir);
float	get_player_speed(t_session *instance);

// display.c
void	mlx_startup(t_session *instance);
void	mlx_update(t_session *instance);
void	mlx_shutdown(t_session *instance);

// dislay_init.c
bool	mlx_vars_init(t_session *instance);
void	destroy_textures(t_session *instance);

// hooks.c
int		handle_key(int keycode, t_session *instance);
int		const_movement(t_session *instance);
int		handle_key_release(int keycode, t_session *instance);
int		handle_single_key(int keycode, t_session *instance);
int		exit_hook(t_session *instance);

// mode_handler
int		handle_mode(int keycode, t_session *instance);
void	handle_door(t_session *instance);
void	close_door(t_session *instance);
void	choose_door_texture(t_session *instance, struct timeval tv);

// pause_menu.c
void	pause_menu(t_session *instance);

// mouse_hooks.c
int		mouse_movement(int x, int y, t_session *instance);
int		ignore_mouse_keys(int button, int x, int y, t_session *instance);

// draw.c
void	pixel_put(t_session *instance, int x, int y, int color);
int		get_pixel(t_data *data, int x, int y);
void	init_dda(t_dda *dda, t_point start, t_point end);
void	draw_line(t_session *instance, t_point start, t_point end, int color);
void	clear_image(t_session *instance);

// load_textures.c
bool	load_textures(t_session *ist);
void	get_tex_data_1(t_session *ist);
void	read_textures(t_session *ist);

// grid.c // debug2D.c
void	debug2D(t_session *instance);
//minimap.c
void	vp_grid(t_session *instance);
void	vp_scaled(t_session *instance);
void	vp_player(t_session *instance, int x, int y);

//minimap utils.c
void	draw_square(t_session *instance, t_point point, int sq, int color);
void	fill_square(t_session *instance, t_point point, int sq, int color);
void	draw_face(t_session *instance, int x, int y, int color);
int		split_size(char **split);
size_t	max_len(char **split);

// start.c
bool	start_game(t_session *instance);
// main.c
void	clean_parser(t_map *map);

#endif
