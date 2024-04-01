#include "../includes/headers/cub3d.h"

bool check_char(t_map *map)
{
	int ctd;
	int ctd2;

	ctd = 0;
	while (map->map[ctd])
	{
		ctd2 = 0;
		while (map->map[ctd][ctd2])
		{
			if (!is_in_array(VALID_CHAR, map->map[ctd][ctd2]))
				return (false);
			ctd2++;
		}
		ctd++;
	}
	return (true);
}

void set_visited(t_map *map)
{
	int cols;
	int rows;

	cols = 0;
	while (map->map[cols])
	{
		rows = 0; 
		while (map->map[cols][rows])
		{
			map->visited[cols][rows] = false;
			rows++;
		}
		cols++;
	}
}

bool initiate_flood(t_map *map)
{
	int cols;
	int rows;

	cols = 0;
	while (map->map[cols])
		cols++;
	map->visited = malloc(sizeof(bool *) * cols);
	if (!map->visited)	
		return (ft_putendl_fd(ERR_ALLOC, 2), false);
	while (cols >= 0)
	{
		rows = 0;
		while (map->map[cols][rows])
			rows++;
		map->visited[cols] = malloc(rows * sizeof(bool));
		if (!map->visited[cols])
			return (ft_putendl_fd(ERR_ALLOC, 2), false);
	}
		cols--;
	set_visited(map);
}

bool validate_map(t_map *map)
{
	if (!check_char(map))
		return (ft_putendl_fd(INV_CHAR, 2), false);
	
	return (true);
}