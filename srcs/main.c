
#include "../includes/headers/cub3d.h"

int	main(int argc, char **argv)
{
	t_session *instance;

	(void)argv;
	if (argc == 2)
	{
		instance = (t_session *)malloc(sizeof(t_session));
		if (!instance)
			return (0);
		instance->map[0] = "111111111111111";
		instance->map[1] = "110000000000101";
		instance->map[2] = "100010000000001";
		instance->map[3] = "100100000000101";
		instance->map[4] = "110000100000111";
		instance->map[5] = "111100001000001";
		instance->map[6] = "100100000000011";
		instance->map[7] = "100000001000111";
		instance->map[8] = "111111111111111";
		instance->map[9] = NULL;
		for (int i = 0; instance->map[i] != NULL; i++)
			printf("%s\n", instance->map[i]);
		mlx_startup(instance);
		mlx_key_hook(instance->mlx_win, handle_key, instance);
		mlx_hook(instance->mlx_win, DestroyNotify, StructureNotifyMask, exit_hook, instance);
		mlx_loop(instance->mlx_ser);
	}
	return (0);
}
