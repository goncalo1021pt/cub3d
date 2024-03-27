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
	int	ctd;

	ctd = 0;
	while (map->buffer[ctd])
	{
		ft_printf("%s\n", map->buffer[ctd]);
		ctd++;
	}
}
