#include "../includes/headers/cub3d.h"

void	set_angle(t_player *player, char angle)
{
	if (angle == 'N')
		player->angle = NORTH;
	else if (angle == 'E')
		player->angle = EAST;
	else if (angle == 'S')
		player->angle = SOUTH;
	else if (angle == 'W')
		player->angle = WEST;
}

void	initialize_player(t_player *player, t_map *map)
{
	int	y;
	int	x;

	y = -1;
	while (map->grid[++y])
	{
		x = -1;
		while (map->grid[y][++x])
		{
			if (is_in_array(PLAYER, map->grid[y][x]))
			{
				player->x = x;
				player->y = y;
				set_angle(player, map->grid[y][x]);
				map->grid[y][x] ='P' ;
				return ;
			}
		}
	}
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
void move_player(t_player *player, t_map *map, int speed, t_keys_angle dir)
{
	int x;
	int y;
	double angle;

	angle = player->angle + dir;
	if (angle >= 360)
		angle -= 360;
	if (angle < 0)
		angle += 360;
	x = player->x;
	y = player->y;
	if (dir == W_ANGLE)
	{
		x = player->x + round(speed * cos(angle * PI / 180));
		y = player->y + round(speed * sin(angle * PI / 180)); 
	}
	else if (dir == S_ANGLE)
	{
		x = player->x + round(speed * +cos(angle * PI / 180));
		y = player->y + round(speed * +sin(angle * PI / 180));
	}
	else if (dir == A_ANGLE)
	{
		x = player->x + round(speed * cos(angle * PI / 180));
		y = player->y + round(speed * sin(angle * PI / 180));
	}
	else if (dir == D_ANGLE)
	{
		x = player->x + round(speed * cos(angle * PI / 180));
		y = player->y + round(speed * sin(angle * PI / 180));
	}
	if (map->grid[y][x] == '0')
	{
		map->grid[player->y][player->x] = '0';
		player->x = x;
		player->y = y;
		map->grid[player->y][player->x] = 'P';
	}
}

