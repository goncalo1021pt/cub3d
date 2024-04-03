#include "../includes/headers/cub3d.h"

bool	start_game(t_map *map)
{
	t_player	player;

	create_grid(map);
	initialize_player(&player, map);
	print_grid(map->grid);
	return (true);
}
