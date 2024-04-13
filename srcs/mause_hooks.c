#include "../includes/headers/cub3d.h"
#define MOUSE_SENSITIVITY 1000

int	mouse_movement(int x, int y, t_session *instance)
{
	(void)y;
	if (x > instance->width / 2)
		rotate_player(&instance->player, RIGHT_ARROW, 0.5);
	else if (x < instance->width / 2)
		rotate_player(&instance->player, LEFT_ARROW, 0.5);
	mlx_mouse_move(instance->mlx_ser, instance->mlx_win, instance->width / 2, instance->height / 2);
	return (0);
}
