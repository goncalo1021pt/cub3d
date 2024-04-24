#include "../../includes/headers/cub3d.h"

int	min(int n1, int n2)
{
	if (n1 < n2)
		return (n1);
	return (n2);
}

int max(int n1, int n2)
{
	if (n1 > n2)
		return (n1);
	return (n2);
}

bool	is_in_colision(int x, int y, t_map *map, char type)
{
	int	ctd;

	ctd = 0;
	while (ctd <= PLAYER_SIZE)
	{
		if (map->grid[y][x + ctd] == type || map->grid[y + ctd][x] == type || map->grid[y + ctd][x + ctd] == type)
			return (true);
		if (map->grid[y - ctd][x] == type || map->grid[y][x - ctd] == type || map->grid[y - ctd][x - ctd] == type)
			return (true);
		ctd++;
	}
	return (false);
}