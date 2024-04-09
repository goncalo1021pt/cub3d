#ifndef STRUCTS_H
# define STRUCTS_H

# include <stdbool.h>

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

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

typedef struct s_player
{
	int		x;
	int		y;
	double	angle;
}			t_player;

typedef struct s_point
{
	int	x;
	int	y;
} t_point;

typedef struct s_session
{
	void			*mlx_ser;
	void			*mlx_win;
	t_data			mlx_img;
	t_map			map;
	t_player		player;
	int				width;
	int				height;
}	t_session;

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

#endif
