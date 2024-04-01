
#include "../includes/headers/cub3d.h"

int	main(int argc, char **argv)
{
	t_session *instance;
	char* map[] = {
		"111111111111111",
		"100000000000101",
		"100010000000001",
		"100100000000101",
		"110000100000111",
		"111100001000001",
		"100100000000011",
		"100000001000111",
		"111111111111111",
		NULL
	};

	(void)argv;
	if (argc == 2)
	{
		instance = (t_session *)malloc(sizeof(t_session));
		if (!instance)
			return (0);
		for (int i = 0; map[i] != NULL; i++)
			printf("%s\n", map[i]);
		mlx_startup(instance);
		mlx_key_hook(instance->mlx_win, handle_key, instance);
		mlx_hook(instance->mlx_win, DestroyNotify, StructureNotifyMask, exit_hook, instance);
		draw_grid(instance, map);
		mlx_loop(instance->mlx_ser);
	}
	return (0);
}
