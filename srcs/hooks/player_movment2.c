#include "../../includes/headers/cub3d.h"

float	get_player_speed(t_session *instance)
{
	float	speed;

	speed = SPEED_MULTIPLIER;
	if (instance->player.keys_pressed > 1)
		speed *= 0.5;
	if (instance->keys[L_SHIFT])
		speed *= 1.5;
	return (speed);
}

void	rotate_player(t_player *player, int angle)
{
	if (angle == RIGHT_ARROW)
		player->angle += ROTATION_SPEED;
	else if (angle == LEFT_ARROW)
		player->angle -= ROTATION_SPEED;
	if (player->angle >= 360)
		player->angle -= 360;
	if (player->angle < 0)
		player->angle += 360;
}
