#include "../includes/headers/cub3d.h"

int	main(int argc, char **argv)
{
	t_map	map;

	init_map(&map);
	if (!parser(argc, argv, &map))
		return (1);
	print_file(&map);
	return (0);
}
