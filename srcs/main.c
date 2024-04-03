#include "../includes/headers/cub3d.h"

void	clean_parser(t_map *map)
{
	if (map->buffer)
		free_file(map->buffer);
	if (map->map)
		free_file(map->map);
	if (map->visited)
		free_file((char **)map->visited);
	if (map->grid)
		free_file(map->grid);
	if (map->no)
		free(map->no);
	if (map->so)
		free(map->so);
	if (map->we)
		free(map->we);
	if (map->ea)
		free(map->ea);
	if (map->c)
		free(map->c);
	if (map->f)
		free(map->f);
}

int	main(int argc, char **argv)
{
	t_map	map;

	init_map(&map);
	if (!parser(argc, argv, &map))
		return (clean_parser(&map), 1);
	start_game(&map);
	clean_parser(&map);
	return (0);
}
