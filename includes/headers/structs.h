#ifndef STRUCTS_H
# define STRUCTS_H

# include <stdbool.h>
# define MAX_KEYS 256

typedef struct s_point
{
	int			x;
	int			y;
}				t_point;

typedef struct s_data
{
	void		*img;
	char		*addr;
	int			bpp;
	int			line_length;
	int			endian;
	int			width;
	int			height;
}				t_data;

typedef struct s_map
{
	char		**buffer;
	char		**grid;
	char		**map;
	bool		**visited;
	char		*no;
	char		*so;
	char		*we;
	char		*ea;
	char		*c;
	char		*f;
	int			colors[2];
	int			grid_h;
	int			grid_w;
}				t_map;

typedef struct s_player
{
	float		x;
	float		y;
	int			keys_pressed;
	double		angle;
}				t_player;

typedef struct s_mode
{
	bool		pause;
	bool		minimap;
}				t_mode;

typedef struct s_session
{
	void		*mlx_ser;
	void		*mlx_win;
	t_data		mlx_img;
	t_data		textures[6];
	t_map		map;
	t_player	player;
	t_mode		mode;
	int			width;
	int			height;
	int			keys[MAX_KEYS];
}				t_session;

typedef struct s_camera2d
{
	t_point		top_l;
	t_point		bot_r;
	t_point		p_pos;
	t_point		size;
	t_point		offset;

}				t_camera2d;

typedef	struct s_camera3D
{
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	double	fov;
	double	x;
} t_camera3D;

typedef struct s_ray
{
	int hit;
	int side;
	int x;
	int y;
	double ray_dir_x;
	double ray_dir_y;
	double delta_dist_x;
	double delta_dist_y;
	double side_dist_x;
	double side_dist_y;
	double perp_wall_dist;
	double step_x;
	double step_y;
	int	wall_dir;
	int	wall_x;
} t_ray;

typedef struct s_dda
{
	float		delta_x;
	float		delta_y;
	float		step;
	float		x_inc;
	float		y_inc;
	float		current_x;
	float		current_y;
}				t_dda;

typedef struct s_slice
{
	int	height;
	int	start;
	int	end;
	int	color;
} t_slice;

typedef struct s_texture
{
	int 	wall_x;
	int		x;
	int		y;
	int		color;
	t_data	*data;
} t_texture;


#endif
