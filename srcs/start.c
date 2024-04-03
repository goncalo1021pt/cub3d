#include "../includes/headers/cub3d.h"

bool	start_game(t_map *map)
{
	t_player	player;

	create_grid(map);
	initialize_player(&player, map);
	// print_grid(map->grid);
	ft_printf("\n");
	ft_printf("move_angle: %d\n", player.angle);
	// rotate_player(&player, RIGHT_ARROW);
	rotate_player(&player, RIGHT_ARROW);
	ft_printf("move_angle: %d\n", player.angle);
	move_player(&player, map, 1, EAST);
	// move_player(&player, map, 1, EAST);
	// move_player(&player, map, 1, EAST);
	// move_player(&player, map, 1, NORTH);
	// move_player(&player, map, 1, NORTH);
	// move_player(&player, map, 1, NORTH);
	// move_player(&player, map, 1, NORTH);
	// move_player(&player, map, 1, NORTH);
	// move_player(&player, map, 1, NORTH);
	print_grid(map->grid);
	return (true);
}
