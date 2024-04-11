#include "../includes/headers/cub3d.h"

void	print_player(t_player *player)
{
	ft_printf("x: %d | y: %d\n", player->x, player->y);
	printf("angle: %lf\n", player->angle);
}

void	init_keys(t_session *instance)
{
	int	i;

	i = 0;
	while (i < MAX_KEYS)
	{
		instance->keys[i] = 0;
		i++;
	}
}

bool	start_game(t_session *instance)
{
	t_map		*map;
	t_player	*player;

	map = &instance->map;
	player = &instance->player;
	create_grid(map);
	initialize_player(player, map);
	init_keys(instance);
	mlx_startup(instance);
	// print_player(player);
	// exit(0);
	return (true);
}
