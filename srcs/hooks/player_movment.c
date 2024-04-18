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
	if (map->grid[(int)round(player->y)][(int)round(x)] == '0')
		player->x = x;
	else if (map->grid[(int)round(y)][(int)round(player->x)] == '0')
		player->y = y;
	else if (x > player->x && map->grid[(int)round(player->y)][(int)round(player->x + 1)] == '0')
			player->x = x;
	else if (x < player->x && map->grid[(int)round(player->y)][(int)round(player->x - 1)] == '0')
			player->x = x;
	else if (y > player->y && map->grid[(int)round(player->y + 1)][(int)round(player->x)] == '0')
			player->y = y;
	else if (y < player->y && map->grid[(int)round(player->y - 1)][(int)round(player->x)] == '0')
			player->y = y;
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
	if (map->grid[(int)round(y)][(int)round(x)] == '0')
	{
		map->grid[(int)round(player->y)][(int)round(player->x)] = '0';
		player->x = x;
		player->y = y;
	}
	else if ((int)angle % 90 != 0)
		wall_slide(player, map, x, y);
}