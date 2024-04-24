#include "../../includes/headers/cub3d.h"

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

void	wall_slide(t_player *player, t_map *map, double x, double y)
{
	if (!is_in_colision((int)round(x), (int)round(player->y), map, '1') && !is_in_colision((int)round(x), (int)round(player->y), map, 'D'))
		player->x = x;
	else if (!is_in_colision((int)round(player->x), (int)round(y), map, '1') && !is_in_colision((int)round(player->x), (int)round(y), map, 'D'))
		player->y = y;
	else if (x > player->x && !is_in_colision((int)round(player->x + 1), (int)round(player->y), map, '1') && !is_in_colision((int)round(player->x + 1), (int)round(player->y), map, 'D'))
		player->x = x;
	else if (x < player->x && !is_in_colision((int)round(player->x - 1), (int)round(player->y), map, '1') && !is_in_colision((int)round(player->x - 1), (int)round(player->y), map, 'D'))
		player->x = x;
	else if (y > player->y && !is_in_colision((int)round(player->x), (int)round(player->y + 1), map, '1') && !is_in_colision((int)round(player->x), (int)round(player->y + 1), map, 'D'))
		player->y = y;
	else if (y < player->y && !is_in_colision((int)round(player->x), (int)round(player->y - 1), map, '1') && !is_in_colision((int)round(player->x), (int)round(player->y - 1), map, 'D'))
		player->y = y;
}

void	meve_door(t_player *player, t_map *map, double x, double y)
{
	printf("door\n");
	if (player->door == true)
	{
		player->x = x;
		player->y = y;
	}
	else
		wall_slide(player, map, x, y);
}

bool	check_collision_door(t_player *player, t_map *map, int x, int y)
{
	int	ctd;

	ctd = min(player->x, x);
	while (ctd <= max(player->x, x))
	{
		if (is_in_colision(ctd, (int)round(y), map, 'D'))
			return (true);
		ctd++;
	}
	ctd = min(player->y, y);
	while (ctd <= max(player->y, y))
	{
		if (is_in_colision((int)round(x), ctd, map, 'D'))
			return (true);
		ctd++;
	}
	return (false);
}

void	move_player(t_player *player, t_map *map, int speed, t_keys_angle dir)
{
	double	x;
	double	y;
	double	angle;

	angle = player->angle + dir;
	if (angle >= 360)
		angle -= 360;
	if (angle < 0)
		angle += 360;
	x = 0;
	y = 0;
	if (dir == W_ANGLE || dir == S_ANGLE || dir == A_ANGLE || dir == D_ANGLE)
	{
		x = player->x + speed * cos(angle * PI / 180);
		y = player->y + speed * sin(angle * PI / 180);
	}
	if (check_collision_door(player, map, x, y))
		meve_door(player, map, x, y);
	else if (!is_in_colision((int)round(x), (int)round(y), map, '1'))
	{
		player->x = x;
		player->y = y;
	}
	else if ((int)angle % 90 != 0)
		wall_slide(player, map, x, y);
}
