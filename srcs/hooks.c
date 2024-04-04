
#include "../includes/headers/cub3d.h"

# define ESC 65307
# define UP 65362
# define DOWN 65364
# define LEFT 65361
# define RIGHT 65363
# define W 119
# define S 115
# define A 97
# define D 100

int	exit_hook(t_session *instance)
{
	mlx_shutdown(instance);
	return (0);
}

int	handle_key(int keycode, t_session *instance)
{
	printf("%d\n", keycode);
	if (keycode == ESC)
		mlx_shutdown(instance);
	if (keycode == W)
		instance->player.y++;
	else if (keycode == S)
		instance->player.y--;
	else if (keycode == A)
		instance->player.x++;
	else if (keycode == D)
		instance->player.x--;
	mlx_update(instance);
	return (0);
}
