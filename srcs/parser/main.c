#include "../../includes/headers/cub3d.h"

int	main(int argc, char **argv)
{
	t_session	instance;

	init_map(&instance.map);
	if (!parser(argc, argv, &instance.map))
		return (clean_parser(&instance.map), 1);
	start_game(&instance);
	return (0);
}
