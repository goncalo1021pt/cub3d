#include "../includes/headers/cub3d.h"

int	main(int argc, char **argv)
{
	t_map	map;

	ft_printf("Start of the program\n");
	if (!parser(argc, argv, &map))
		return (1);
	return (0);
}
