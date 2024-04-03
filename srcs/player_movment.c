#include "../includes/headers/cub3d.h"

void set_angle(t_player *player, char angle)
{
	if (angle == 'N')
		player->angle = 0;
	else if (angle == 'E')
		player->angle = 90;
	else if (angle == 'S')
		player->angle = 180;
	else if (angle == 'W')
		player->angle = 270;
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
