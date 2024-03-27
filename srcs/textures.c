#include "../includes/headers/cub3d.h"

void	init_textures(t_map *map)
{
	map->no = NULL;
	map->so = NULL;
	map->we = NULL;
	map->ea = NULL;
}

bool	get_textures(t_map *map)
{
	init_textures(map);
	return (true);
}
