
#include "../includes/headers/cub3d.h"

# define ESC 65307

int	exit_hook(t_session *instance)
{
	mlx_shutdown(instance);
	return (0);
}

int	handle_key(int keycode, t_session *instance)
{
	if (keycode == ESC)
		mlx_shutdown(instance);
	return (0);
}
