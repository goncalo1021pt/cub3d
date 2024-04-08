
#include "../includes/headers/cub3d.h"

int	exit_hook(t_session *instance)
{
	mlx_shutdown(instance);
	return (0);
}

int	handle_key(int keycode, t_session *instance)
{
	printf("\033[1;33mINPUT -> %d <- /////\033[0m\n", keycode);
	if (keycode == ESC)
		mlx_shutdown(instance);
	if (keycode == W)
		move_player(&instance->player, &instance->map, 1, W_ANGLE);
	else if (keycode == S)
		move_player(&instance->player, &instance->map, 1, S_ANGLE);
	else if (keycode == A)
		move_player(&instance->player, &instance->map, 1, A_ANGLE);
	else if (keycode == D)
		move_player(&instance->player, &instance->map, 1, D_ANGLE);
	mlx_update(instance);
	return (0);
}
