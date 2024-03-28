#include "../includes/headers/cub3d.h"

void	free_file(t_map *map)
{
	int	ctd;

	ctd = 0;
	while (map->buffer[ctd])
	{
		free(map->buffer[ctd]);
		ctd++;
	}
	free(map->buffer);
}

void	print_file(t_map *map)
{
	// int	ctd;

	// ctd = 0;
	printf("NO: %s\n", map->no);
	printf("SO: %s\n", map->so);
	printf("WE: %s\n", map->we);
	printf("EA: %s\n", map->ea);
	printf("C: %s\n", map->c);
	printf("F: %s\n", map->f);
	// while (map->buffer[ctd])
	// {
	// 	ft_printf("%s\n", map->buffer[ctd]);
	// 	ctd++;
	// }
}

void	init_map(t_map *map)
{
	map->buffer = NULL;
	map->map = NULL;
	map->no = NULL;
	map->so = NULL;
	map->we = NULL;
	map->ea = NULL;
	map->c = NULL;
	map->f = NULL;
}
