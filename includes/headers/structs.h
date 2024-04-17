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
}				t_map;

// typedef struct s_ray
// {
// 	t_point col_point;
// 	int		texture;
// 	float 	len;
// 	float 	angle;
// } t_ray;

<<<<<<< HEAD
typedef struct s_ray 
{
	t_point	col_point;
	int		texture;
	int 	len;
	float 	angle;
} t_ray;

typedef struct s_rcaster
{
	float	fov;
	float	angle;
	float 	inc;
	int		len;
	int		n_rays;
	t_ray	rays[1980];	
} t_rcaster;
=======
// typedef struct s_rcaster
// {
// 	float	fov;
// 	float	angle;
// 	float 	inc;
// 	float	len;
// 	int		n_rays;
// 	t_ray	rays[1980];
// } t_rcaster;
>>>>>>> raycaster

typedef struct s_player
{
	float		x;
	float		y;
	int			keys_pressed;
	double		angle;
	//t_rcaster	raycaster;
}				t_player;

typedef struct s_session
{
	void		*mlx_ser;
	void		*mlx_win;
	t_data		mlx_img;
	t_data		textures[6];
	t_map		map;
	t_player	player;
	int			mode;
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

#endif
