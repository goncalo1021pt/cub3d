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

void	print_grid(char **grid)
{
	int	ctd;

	ctd = 0;
	while (grid[ctd])
	{
		ft_printf("%s\n", grid[ctd]);
		ctd++;
	}
}

int	main(int argc, char **argv)
{
	t_map	map;

	init_map(&map);
	if (!parser(argc, argv, &map))
		return (clean_parser(&map), 1);
	print_file(&map);
	create_grid(&map);
	clean_parser(&map);
	return (0);
}
