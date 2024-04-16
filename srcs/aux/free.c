#include "../../includes/headers/cub3d.h"

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

void	free_file(char **arr_str)
{
	int	ctd;

	ctd = 0;
	while (arr_str[ctd])
	{
		free(arr_str[ctd]);
		ctd++;
	}
	free(arr_str);
}

