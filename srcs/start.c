#include "../includes/headers/cub3d.h"

void	print_player(t_player *player)
{
	ft_printf("x: %d | y: %d\n", player->x, player->y);
	printf("angle: %lf\n", player->angle);
}

bool	start_game(t_map *map, t_player	*player)
{

	create_grid(map);
	initialize_player(player, map);
	// print_player(player);
	// exit(0);
	return (true);
}
