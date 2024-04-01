#ifndef DISPLAY_H
# define DISPLAY_H

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef struct s_session
{
	void		*mlx_ser;
	void		*mlx_win;
	t_data		mlx_img;
	int			width;
	int			height;
}	t_session;

typedef struct s_grid
{
	int	y;
	int	x;
	int	row_s;
	int	col_s;
	int	sq_h;
	int	sq_w;
	int	top_y;
	int	top_x;
}	t_grid;

typedef struct s_dda
{
	float	delta_x;
	float	delta_y;
	float	step;
	float	x_inc;
	float	y_inc;
	float	current_x;
	float	current_y;
}	t_dda;

// display.c
void	mlx_startup(t_session *instance);
void	mlx_shutdown(t_session *instance);
void	pixel_put(t_data *data, int x, int y, int color);
// hooks.c
int		handle_key(int keycode, t_session *instance);
int		exit_hook(t_session *instance);
// draw.c
void	init_dda(t_dda *dda, int start_x, int start_y , int end_x, int end_y);
void	draw_line(t_session *instance, int start_x, int end_x, int start_y, int end_y);
// grid.c
void draw_grid(t_session *instance, char **map);

#endif
