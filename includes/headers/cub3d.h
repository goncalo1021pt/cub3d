#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include "../minilibx-linux/mlx.h"
# include "../minilibx-linux/mlx_int.h"
# include "messages.h"
# include <errno.h>
# include <fcntl.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define W_WIDTH 1920
# define W_HEIGHT 1080

typedef struct s_map
{
	char	**buffer;
	char	**map;
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	char	*s;
	char	*f;
}			t_map;

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

// parser.c
bool		parser(int argc, char **argv, t_map *map);

// map_aux.c
void		print_file(t_map *map);
void		init_map(t_map *map);

// textures.c
bool		get_textures(t_map *map);
// display.c
void	mlx_startup(t_session *instance);
void	mlx_shutdown(t_session *instance);
int		handle_key(int keycode, t_session *instance);
int		exit_hook(t_session *instance);


#endif
