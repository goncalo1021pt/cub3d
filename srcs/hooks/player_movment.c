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

bool	is_in_colision(int x, int y, t_map *map, bool door_is_open)
{
	int	ctd;

	ctd = 0;
	(void)door_is_open;
	while (ctd <= HIT_BOX)
	{
		if (map->grid[y][x + ctd] == '1' || map->grid[y + ctd][x] == '1' || map->grid[y + ctd][x + ctd] == '1')
			return (true);
		if (map->grid[y - ctd][x] == '1' || map->grid[y][x - ctd] == '1' || map->grid[y - ctd][x - ctd] == '1')
			return (true);
		ctd++;
	}
	return (false);
}

void wall_slide(t_player *player, t_map *map, double x, double y)
{
    if (!is_in_colision((int)round(x), (int)round(player->y), map, false))
        player->x = x;
    else if (!is_in_colision((int)round(player->x), (int)round(y), map, false))
        player->y = y;
    else if (x > player->x && !is_in_colision((int)round(player->x + 1), (int)round(player->y), map, false))
        player->x = x;
    else if (x < player->x && !is_in_colision((int)round(player->x - 1), (int)round(player->y), map, false))
        player->x = x;
    else if (y > player->y && !is_in_colision((int)round(player->x), (int)round(player->y + 1), map, false))
        player->y = y;
    else if (y < player->y && !is_in_colision((int)round(player->x), (int)round(player->y - 1), map, false))
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
	if (!is_in_colision((int)round(x), (int)round(y), map, false))
	{
		map->grid[(int)round(player->y)][(int)round(player->x)] = '0';
		player->x = x;
		player->y = y;
	}
	else if ((int)angle % 90 != 0)
		wall_slide(player, map, x, y);
}
