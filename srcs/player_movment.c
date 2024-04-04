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
	int	ctd;
	int	ctd2;

	ctd = -1;
	while (map->grid[++ctd])
	{
		ctd2 = -1;
		while (map->grid[ctd][++ctd2])
		{
			if (is_in_array(PLAYER, map->grid[ctd][ctd2]))
			{
				player->x = ctd;
				player->y = ctd2;
				set_angle(player, map->grid[ctd][ctd2]);
				map->grid[ctd][ctd2] = 'P';
				return ;
			}
		}
	}
}

void	rotate_player(t_player *player, int angle)
{
	if (angle == RIGHT_ARROW)
		player->angle -= ROTATION_SPEED;
	else if (angle == LEFT_ARROW)
		player->angle += ROTATION_SPEED;
	if (player->angle >= 360)
		player->angle -= 360;
	if (player->angle < 0)
		player->angle += 360;
}

void	move_player(t_player *player, t_map *map, int speed, t_dir dir)
{
	int		x;
	int		y;
	double	angle;

	(void)speed;
	angle = player->angle + dir;
	if (angle >= 360)
		angle -= 360;
	if (angle < 0)
		angle += 360;
	x = player->x + 1;//(cos(angle * PI / 180) * speed);
	y = player->y + 1;//(sin(angle * PI / 180) * speed);
	if (map->grid[x][y] == '0')
	{
		map->grid[player->x][player->y] = '0';
		player->x = x;
		player->y = y;
		map->grid[player->x][player->y] = 'P';
	}
}
